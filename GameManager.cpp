//GameManager.cpp: ��Ϸ���������� ��һЩʵ�ú���

#include "GameManager.h"
#include "Define.h"
#include "Note.h"
#include "Particle.h"
#include "ParticleManager.h"

#include <qpainter.h>
#include <qevent.h>
#include <qtimer.h>
#include <qdebug.h>
#include <qtime>

#include <fstream>
#include <algorithm>
#include <random>
#include <qdatetime.h>



namespace
{
	//��qkey����ת������Ӧ����ĸ
	inline char QKey2Ch(int key)
	{
		return key - Qt::Key::Key_A + 'a';
	}

	//����ĸת������Ӧ��qkey����
	inline int Ch2QKey(char ch)
	{
		return ch - 'a' + Qt::Key::Key_A;
	}

	//��ȡĳ�������ڼ����е�x����
	int GetKeyPosX(char ch)
	{
		int x = Def::keyIndexX[ch - 'a'];
		int y = Def::keyIndexY[ch - 'a'];
		int offset = (3.0 - y) / 2.0 * Def::keySize + Def::keyboardPosX;
		return offset + (x - 0.5) * Def::keySize + (x - 1.0) * Def::keySpace;
	}

	//��ȡĳ�������ڼ����е�y����
	int GetKeyPosY(char ch)
	{
		int y = Def::keyIndexY[ch - 'a'];
		return Def::keyboardPosY + (y - 0.5) * Def::keySize + (y - 1.0) * Def::keySpace;
	}

	//��������ɫ֮�����Բ�ֵ
	QColor Lerp(const QColor& s, const QColor& t, double rate)
	{
		int r = s.red() + (t.red() - s.red()) * rate;
		int g = s.green() + (t.green() - s.green()) * rate;
		int b = s.blue() + (t.blue() - s.blue()) * rate;
		return QColor(r, g, b);
	}
}



namespace
{
	GameManager* instance = nullptr;
}

GameManager* GameManager::GetInstance()
{
	if (!instance)
	{
		instance = new GameManager();
	}
	return instance;
}

void GameManager::ReleaseInstance()
{
	delete instance;
}



GameManager::GameManager()
	: QWidget()
{
	this->hide();

	timerId = QObject::startTimer(1, Qt::TimerType::PreciseTimer);
	
	clock = new QTime();

	interfaceImage	= new QImage((Def::resPath + "tex/interface.png").c_str());
	keyImage		= new QImage((Def::resPath + "tex/key.png").c_str());
	keyDownImage	= new QImage((Def::resPath + "tex/key_down.png").c_str());

	ResetAll();
}

GameManager::~GameManager()
{
	ResetAll();

	delete clock;

	delete interfaceImage;
	delete keyImage;
	delete keyDownImage;
}



int GameManager::GetStat() const
{
	return stat;
}



void GameManager::ResetAll()
{
	ParticleManager::GetInstacne()->Clear();

	for (auto note : notes)
	{
		delete note;
	}
	notes.clear();

	keys.clear();

	keyHolding.clear();

	words.clear();

	levelName = std::string("Null");

	stat = GameStat::preparing;

	bonusMode = BonusMode::noBonus;
	bonusStartTime = -100000;
	nextBonusCombo = Def::bonusCombo;

	noteCount = 0;

	time = 0;

	combo = 0;

	score = scoreDisplaying = 0;

	health = Def::maxHealth;

	fever = 0.0;
	feverStartTime = -Def::feverTime * 2;
	feverMode = FeverMode::notFever;

	for (int ch = 'a'; ch <= 'z'; ch++)
	{
		keyColor[ch] = Qt::black;
	}
	bottomLightColor = Qt::black;
	bottomLightHeight = 0.65;
	healthBarColor = Qt::black;
	feverBarColor = Qt::black;
	comboBarColor = Qt::black;
	scoreBarColor = Qt::black;

	trackShake = 0.0;
}

void GameManager::InitNotes()
{
	for (auto note : notes)
	{
		delete note;
	}
	notes.clear();

	//�Ե��ʽ������ɢ��
	for (int i = 0; i < words.size(); i++)
	{
		std::swap(words[i], words[Def::RandInt(0, i)]);
	}

	for (auto& word : words)
	{
		for (auto ch = word.begin(); ch != word.end(); ch++)
		{
			if (isalpha(*ch))
			{
				notes.push_back(new Note(tolower(*ch), 0.0, Def::trackHeight, ch == word.begin()));
			}
		}
	}
}

bool GameManager::LoadLevel(const std::string& name)
{
	std::string path = Def::resPath + "level/" + name + ".lv";

	std::ifstream in(path);

	if (!in)
	{
		qDebug() << ("[ERR] Failed to open file " + path).c_str();
		return false;
	}

	std::getline(in, levelName);
	in.get();

	while(in)
	{
		std::string word;
		in >> word;
		words.push_back(word);
	}
	
	in.close();
	return true;
}



bool GameManager::OnStart(const std::string& name)
{
	ResetAll();

	if (!LoadLevel(name))
	{
		qDebug() << "[ERR] Failed to start game";
		return false;
	}

	InitNotes();

	stat = GameStat::running;
	qDebug() << "[INFO] Game started";

	return true;
}

void GameManager::OnPause()
{
	stat = GameStat::paused;
	qDebug() << "[INFO] Game paused";
}

void GameManager::OnResume()
{
	stat = GameStat::running;
	qDebug() << "[INFO] Game continued";
}

void GameManager::OnExit()
{
	ResetAll();
}

void GameManager::OnKeyPressEvent(int key)
{
	if (!keyHolding[key])
	{
		keyHolding[key] = true;
		keys.push_back(key);
	}
}

void GameManager::OnKeyReleaseEvent(int key)
{
	keyHolding[key] = false;
}



void GameManager::timerEvent(QTimerEvent* event)
{
	if (event->timerId() != this->timerId)
	{
		return;
	}

	static int updateTime	= 0;
	
	while (updateTime >= Def::tickTime) 
	{
		updateTime -= Def::tickTime;
		Update();
	}

	updateTime	+= clock->elapsed();
	clock->start();
}



void GameManager::Update()
{
	if (stat == GameStat::running)
	{
		//-----------------------------------��Ϸ����--------------------------------------//

		time += Def::tickTime;

		//-----------------------------------������Ϸ����----------------------------------//

		double process = std::min(1.0,
			std::atan(
				sqrt(
					noteCount
					* (feverMode == FeverMode::fever ? Def::feverProcessSpeedUp : 1.0)
					* Def::diffIncreaseSpeed
					* (1.0 + fever / Def::maxFever * (Def::noteProcessFeverEffect - 1.0)) + 1.0)
				- 1.0
			)
			/ Def::pi * 2.0);

		//---------------���µ�ǰ�ַ�������ٶȣ��������ϵ����������----------------------//

		{
			noteSpeed		= (1.0 - process) * Def::noteSpeedStart		+ process * Def::noteSpeedEnd;
			noteSlowDown	= (1.0 - process) * Def::noteSlowDownStart	+ process * Def::noteSlowDownEnd;
			noteInterval	= (1.0 - process) * Def::noteIntervalStart	+ process * Def::noteIntervalEnd
							   - (feverMode == FeverMode::fever ? 0.05 : 0.0);
			//���㽱��ģʽ�Ĺ���
			if (bonusMode == BonusMode::fast)
			{
				noteSpeed *= 1.3;
				noteInterval *= 0.85;
			}
			else if (bonusMode == BonusMode::slow)
			{
				noteSpeed *= 0.5;
				noteInterval *= 1.1;
			}
			else if (bonusMode != BonusMode::noBonus)
			{
				noteSpeed *= 0.8;
			}
		}

		//--------------------------------�����Ӿ�Ч��------------------------------------//

		{
			//���¼��̰����ķ�����ɫ
			for (char ch = 'a'; ch <= 'z'; ch++)
			{
				QColor color = Lerp(Qt::black, feverBarColor,
					(feverMode == FeverMode::fever ? std::sin(((GetKeyPosX(ch) + GetKeyPosY(ch)) * 1000 + time) / 1000.0) * 1.0 : 0.0));
				keyColor[ch] = Lerp(keyColor[ch], color, 0.02);
			}

			//�������ײ�������ɫ
			if (health <= Def::maxHealth / 5)
			{
				//��Ѫ��ʱ��ɫ����
				bottomLightColor = Lerp(bottomLightColor,
					QColor(std::max(0.0, (std::sin(time / 1000.0 * Def::pi * 2.0) + 0.8) / 1.8) * 255, 0.0, 0.0)
					, 0.05);
			}
			else
			{
				double light = fever / Def::maxFever * std::max(0.0, (std::sin(time / 1000.0 * Def::pi * 2.0) + 1.0) * 0.25 + 0.5);

				if (bonusMode != BonusMode::noBonus)
				{
					//����ģʽ��Ӧ����ɫ
					bottomLightColor = Lerp(bottomLightColor, Def::bonusColor[bonusMode], 0.05);
				}
				else
				{
					//fever��Ӱ��Ĺ�Ч
					QColor color = Lerp(QColor(feverBarColor.red() * light, feverBarColor.green() * light, feverBarColor.blue() * light),
						Qt::white,
						feverMode == FeverMode::fever ? 0.5 : 0.0);
					bottomLightColor = Lerp(bottomLightColor, color, 0.05);
				}
			}
			//�������ײ����⽥��ĸ߶�
			bottomLightHeight += ((feverMode == FeverMode::fever ? 1.0 : 0.65) - bottomLightHeight) * 0.01;

			//��������
			trackShake *= (1.0 - Def::trackShakeDecreseSpeed);
			if (trackShake < 1.0) trackShake = 0.0;

			//�����������fever�µ�����
			if (feverMode == FeverMode::fever)
			{
				scoreBarColor = (time / 100) & 1 ? Qt::green : Qt::yellow;
			}
			else
			{
				scoreBarColor = Qt::green;
			}

			//������ԭ��ɫ
			comboBarColor = Lerp(comboBarColor, QColor(Qt::yellow), 0.1);
			//������ԭ��ɫ
			scoreBarColor = Lerp(scoreBarColor, QColor(Qt::green), 0.1);
			//fever��ԭ��ɫ
			double feverFactor = double(fever) / Def::maxFever;
			int r = std::max(0.0, std::min(255.0, feverFactor * 200 + 55));
			int g = std::max(0.0, std::min(255.0, feverFactor * 100));
			int b = std::max(0.0, std::min(255.0, feverFactor * 55 + 200));
			feverBarColor = Lerp(feverBarColor, QColor(r, g, b), 0.1);
			//hp��ԭ��ɫ
			double hpFactor = health / double(Def::maxHealth);
			r = std::max(0.0, std::min(255.0, (1.0 - hpFactor) * 200 + 55));
			g = std::max(0.0, std::min(255.0, (hpFactor * 200 + 50)));
			b = std::max(0.0, std::min(255.0, 10.0));
			healthBarColor = Lerp(healthBarColor, QColor(r, g, b), 0.1);

			//����ʵ����ʾ�ķ���
			if (scoreDisplaying != score)
			{
				if (abs(scoreDisplaying - score) <= 50)
				{
					scoreDisplaying += scoreDisplaying < score ? 1 : -1;
				}
				else
				{
					scoreDisplaying += scoreDisplaying < score ? 10 : -10;
				}
			}
		}

		//--------------------------------����������------------------------------------//

		{
			for (auto key : keys)
			{
				if (key > Qt::Key::Key_Z || key < Qt::Key::Key_A)
				{
					continue;
				}

				for (auto note : notes)
				{
					//����note
					if (note->stat == NoteStat::visible && QKey2Ch(key) == note->ch)
					{
						note->stat = NoteStat::cleared;
						noteCount += feverMode != FeverMode::fever;

						//������Ϸ��Ϣ
						{
							health += Def::comboHealth
								* (feverMode == FeverMode::fever ? 5 : 1)
								* (bonusMode != BonusMode::noBonus ? 2 : 1);

							score += Def::noteBasicScore
								* (feverMode == FeverMode::fever ? 2 : 1)
								* (bonusMode != BonusMode::noBonus ? 2 : 1)
								+ combo * Def::comboBonusScore
								* (feverMode == FeverMode::fever ? 5 : 1);

							fever += Def::feverIncreaseSpeed;

							combo++;
						}

						//�����Ӿ���Ϣ
						{
							bottomLightColor = feverMode == FeverMode::fever ? Qt::white : Qt::green;
							keyColor[note->ch] = Qt::green;
							feverBarColor = Qt::white;
							comboBarColor = Qt::white;
						}

						//��ý���Ч��
						if (feverMode == FeverMode::notFever
							&& bonusMode == BonusMode::noBonus
							&& note->bonus != BonusMode::noBonus)
						{
							bonusMode = note->bonus;
							bonusStartTime = time;
							score += Def::bonusScore;
						}

						//����note��������Ч��
						auto p = Def::noteClearParticle;
						for (int i = 0; i < Def::noteClearParticleNum; i++)
						{
							p.color = note->particleColor;
							p.v = ParticleManager::GetRandomVelocity(200.0, false, 100.0);
							p.pos = std::make_pair(note->x + p.v.first / 200.0 * Def::keySize * 0.5, note->y + p.v.second / 200.0 * Def::keySize * 0.5);
							ParticleManager::GetInstacne()->Cast(time, p);
						}

						break;
					}
					//������
					else if (note->stat == NoteStat::visible)
					{
						if (key != Qt::Key::Key_Space)
						{
							note->stat = NoteStat::lost;
							noteCount += feverMode != FeverMode::fever;

							//������Ϸ��Ϣ
							{
								health += Def::noteMissHealth
									/ (feverMode == FeverMode::fever ? 5 : 1)
									/ (bonusMode != BonusMode::noBonus ? 2 : 1);

								score += Def::noteMissScore
									/ (feverMode == FeverMode::fever ? 2 : 1);

								combo = 0;

								nextBonusCombo = Def::bonusCombo;
							}

							//�����Ӿ���Ϣ
							{
								if (feverMode != FeverMode::fever)
									bottomLightColor = Qt::red;
								keyColor[QKey2Ch(key)] = Qt::red;
								healthBarColor = Qt::white;
								comboBarColor = Qt::red;
								trackShake = Def::maxTrackShake * (feverMode == FeverMode::fever ? 0 : 1);
							}

							//���䰴��note����Ч��
							auto p = Def::noteLostParticle;
							for (int i = 0; i < Def::noteLostParticleNum; i++)
							{
								p.v = ParticleManager::GetRandomVelocity(200.0, false, 100.0);
								p.pos = std::make_pair(note->x + p.v.first / 200.0 * Def::keySize * 0.5, note->y + p.v.second / 200.0 * Def::keySize * 0.5);
								ParticleManager::GetInstacne()->Cast(time, p);
							}
						}
						break;
					}

				}
			}

			keys.clear();
		}

		//--------------------------------����note---------------------------------------//

		{
			//�Ƿ���ʣ�µ�note
			bool hasRestNotes = false;

			//ʵ�ʵ�note���
			int interval = noteInterval * noteSpeed;

			double lastNoteY = -100.0 * Def::trackHeight;
			double lastNoteX = Def::noteTrackWidth / 2;

			for (auto note : notes)
			{
				//������ʾ�е�note��y����
				if (note->stat != NoteStat::hidden)
				{
					note->y -= noteSpeed * (1.0 - noteSlowDown * (1.0 - note->y / Def::trackHeight)) / 1000.0 * Def::tickTime;
				}

				//δ�����note���㿪ʼ�������� ��ʼ���䣨�����׸���ĸǰ�ж�������
				if (note->stat == NoteStat::hidden && Def::trackHeight - lastNoteY
					>= interval * (note->wordBegin ? (feverMode == FeverMode::fever ? 2.5 : 2) : 1))
				{
					note->stat = NoteStat::visible;

					//������������note���ӽ���
					if (bonusMode == BonusMode::noBonus 
						&& feverMode == FeverMode::notFever
						&& combo > nextBonusCombo 
						&& Def::RandInt(1, 5) == 1)
					{
						note->bonus = Def::RandInt(1, BonusMode::bonusNum - 1);
						nextBonusCombo = combo + Def::bonusCombo;
					}

					//���ݲ�ͬ����ģʽ������note������
					if (bonusMode == BonusMode::random)
					{
						note->x = Def::RandInt(20, Def::trackWidth - 20);
					}
					else if (bonusMode == BonusMode::reverse)
					{
						note->x = lastNoteX - Def::noteTrackWidth;
						if (note->x <= Def::noteTrackWidth / 2)
						{
							note->x = Def::trackWidth - Def::noteTrackWidth / 2;
						}
					}
					else
					{
						note->x = lastNoteX + Def::noteTrackWidth;
						if (note->x >= Def::trackWidth - Def::noteTrackWidth / 2)
						{
							note->x = Def::noteTrackWidth / 2;
						}
					}

					//��ʼ����
					note->y = Def::trackHeight;
				}

				//note�䵽�ײ��ж�
				if (note->stat == NoteStat::visible && note->y <= 0)
				{
					note->stat = NoteStat::lost;
					noteCount += feverMode != FeverMode::fever;

					//������Ϸ������Ϣ
					{
						health += Def::noteLostHealth
							/ (feverMode == FeverMode::fever ? 5 : 1)
							/ (bonusMode != BonusMode::noBonus ? 2 : 1);

						score += Def::noteLostScore
							/ (feverMode == FeverMode::fever ? 2 : 1);

						combo = 0;
					}

					//�����Ӿ�Ч��
					{
						keyColor[note->ch] = Qt::red;
						if (feverMode != FeverMode::fever)
							bottomLightColor = Qt::red;
						healthBarColor = Qt::white;
						comboBarColor = Qt::red;
						trackShake = Def::maxTrackShake * (feverMode == FeverMode::fever ? 0 : 1);
					}

					//����note©������Ч��
					auto p = Def::noteLostParticle;
					for (int i = 0; i < Def::noteLostParticleNum; i++)
					{
						p.v = ParticleManager::GetRandomVelocity(200.0, false, 100.0);
						p.pos = std::make_pair(note->x + p.v.first / 200.0 * Def::keySize * 0.5, note->y + p.v.second / 200.0 * Def::keySize * 0.5);
						ParticleManager::GetInstacne()->Cast(time, p);
					}
				}

				//�ж��Ƿ����ʣ���note �����õ�һ��note�ļ�����ɫ��ʾ
				if (note->stat == NoteStat::visible || note->stat == NoteStat::hidden)
				{
					if (!hasRestNotes)
					{
						keyColor[note->ch] = Qt::yellow;
					}
					hasRestNotes = true;
				}

				//��ʾ�е�note����β����Ч��
				if (note->stat == NoteStat::visible)
				{
					//�̶��������
					if (time - note->lastCastDragParticleTime > Def::noteDragParticleInterval)
					{
						auto p = Def::noteDragParticle;
						p.color = note->particleColor;
						p.v = ParticleManager::GetRandomVelocity(20.0, false, 0.0);
						p.pos = ParticleManager::GetRandomSquarePos(
							note->x - Def::keySize * 0.3,
							note->y + Def::keySize * 0.4,
							note->x + Def::keySize * 0.3,
							note->y + Def::keySize * 0.2
						);
						ParticleManager::GetInstacne()->Cast(time, p);
						note->lastCastDragParticleTime = time;
					}
				}

				lastNoteX = note->x;
				lastNoteY = note->y;
			}

			//���û��note�����¼���
			if (!hasRestNotes)
			{
				InitNotes();
			}
		}

		//-------------------------------����fever�ͽ���-------------------------------//
		{
			//����fever�ȴ� ��ս���
			if (fever >= Def::maxFever && feverMode == FeverMode::notFever)
			{
				feverStartTime = time;
				feverMode = FeverMode::standby;
				bonusMode = BonusMode::noBonus;
			}
			//fever��ʼ
			else if (time - feverStartTime >= Def::feverStandByTime && feverMode == FeverMode::standby)
			{
				feverMode = FeverMode::fever;
				trackShake = Def::maxTrackShake * 2.0;
			}
			//fever����
			else if (fever < 0.5 && feverMode == FeverMode::fever)
			{
				feverMode = FeverMode::notFever;
				nextBonusCombo = combo + Def::bonusCombo;
			}

			//fever�ͷ�feverģʽ�µ�fever���½��ٶ�
			if (feverMode == FeverMode::notFever)
			{
				fever -= 1.0 / noteInterval * Def::feverIncreaseSpeed * 0.5 / 1000. * Def::tickTime;
			}
			else if (feverMode == FeverMode::fever)
			{
				fever -= Def::maxFever / Def::feverTime * Def::tickTime;
			}

			//feverģʽ�µ�����Ч��
			if (feverMode == FeverMode::fever)
			{
				static int lastCastFeverParticleTime = time;
				if (time - lastCastFeverParticleTime >= Def::feverParticleInterval)
				{
					lastCastFeverParticleTime = time;
					auto p = Def::feverParticle;
					p.pos = ParticleManager::GetRandomSquarePos(10, Def::trackHeight + 10, Def::trackWidth - 10, Def::trackHeight + 10);
					p.v = std::make_pair(0, -noteSpeed);
					p.color = bottomLightColor;
					ParticleManager::GetInstacne()->Cast(time, p);
				}
			}

			//����ģʽ�Ľ���
			if (bonusMode != BonusMode::noBonus && time - bonusStartTime > Def::bonusTime[bonusMode])
			{
				bonusMode = BonusMode::noBonus;
				nextBonusCombo = combo + Def::bonusCombo;
			}
		}

		

		//-----------------------------------�����Ϸ����-----------------------------------//
		
		health = std::min(Def::maxHealth, std::max(health, 0));
		fever = std::min(Def::maxFever, std::max(fever, 0.0));

		if (health == 0)
		{
			ResetAll();
			emit GameOverSignal(GameRecord{ score, levelName, QDateTime::currentDateTime().toString().toStdString() });
		}

		//----------------------------------�������ӹ�����-----------------------------------//

		ParticleManager::GetInstacne()->Update(time);

	}
}



void GameManager::DrawTrack(QPainter* painter) const
{
	painter->setPen(Qt::black);

	double shakeX = std::sin(time) * trackShake;
	double shakeY = std::cos(time) * trackShake;

	painter->translate(Def::trackPosX + shakeX, Def::trackPosY + shakeY);

	//draw background
	QLinearGradient grad(QPointF(0, -Def::trackHeight), QPointF(0, Def::trackHeight));
	grad.setColorAt(0.3, bottomLightColor);
	grad.setColorAt(bottomLightHeight, Qt::black);
	painter->setBrush(QBrush(grad));
	painter->drawRect(QRect(-2, -2, Def::trackWidth + 4, Def::trackHeight + 4));

	if (stat == GameStat::running)
	{
		//draw fever text
		if (feverMode == FeverMode::standby)
		{
			auto font = painter->font();
			font.setPixelSize(40);
			painter->setFont(font);
			QFontMetrics m(painter->font());
			int fontSizeX = m.width("FEVER STANDBY");
			int fontSizeY = m.height();

			painter->translate(Def::trackWidth / 2, Def::trackHeight / 2);

			QColor color = Lerp(feverBarColor, Qt::black, 0.5);
			painter->setPen(color);

			painter->scale(1.0, -1.0);
			painter->drawText(-fontSizeX / 2, -5, "FEVER STANDBY");
			painter->scale(1.0, -1.0);

			int sec = (Def::feverStandByTime - time + feverStartTime) / 1000 + 1;

			font = painter->font();
			font.setPixelSize(70);
			painter->setFont(font);
			m = QFontMetrics(painter->font());

			if ((time / (20 + sec * 20)) & 1)
			{
				color = Lerp(color, Qt::white, 0.5);
			}
			fontSizeX = m.width(std::to_string(sec).c_str());
			fontSizeY = m.height();

			painter->setPen(color);
			painter->scale(1.0, -1.0);
			painter->drawText(-fontSizeX / 2, fontSizeY, std::to_string(sec).c_str());
			painter->scale(1.0, -1.0);

			painter->translate(-Def::trackWidth / 2, -Def::trackHeight / 2);
		}

		//draw bonus text
		if (bonusMode != BonusMode::noBonus)
		{
			auto font = painter->font();
			font.setPixelSize(50);
			painter->setFont(font);
			QFontMetrics m(painter->font());
			int fontSizeX = m.width(Def::bonusTitle[bonusMode].c_str());
			int fontSizeY = m.height();

			painter->translate(Def::trackWidth / 2, Def::trackHeight / 2);

			QColor color = Lerp(Def::bonusColor[bonusMode], Qt::black, 0.5);
			painter->setPen(color);

			painter->setOpacity(std::max(0.0, ((2000.0 - (time - bonusStartTime)) / 2000.0)));
			painter->scale(bonusMode == BonusMode::reverse ? -1.0 : 1.0, -1.0);
			painter->drawText(-fontSizeX / 2, -fontSizeY / 2, Def::bonusTitle[bonusMode].c_str());
			painter->scale(bonusMode == BonusMode::reverse ? -1.0 : 1.0, -1.0);
			painter->setOpacity(1.0);

			painter->translate(-Def::trackWidth / 2, -Def::trackHeight / 2);
		}

		QFont font = painter->font();
		font.setPixelSize(Def::noteSize);
		font.setBold(false);
		painter->setFont(font);

		//draw note
		bool first = true;
		for (auto note : notes)
		{
			if (note->stat == NoteStat::visible)
			{
				note->Draw(painter, first, feverMode == FeverMode::fever);
				first = false;
			}
		}
	}

	painter->translate(-Def::trackPosX - shakeX, -Def::trackPosY - shakeY);
}

void GameManager::DrawGui(QPainter* painter) const
{
	//draw score
	{
		int scoreFontSize = 25;
		int scoreWidth = Def::trackWidth * 0.5;
		int scoreHeight = scoreFontSize * 2 + 20;

		QFont font = painter->font();
		font.setPixelSize(scoreFontSize);
		font.setBold(false);
		painter->setFont(font);

		painter->translate(Def::scorePosX, Def::scorePosY);

		painter->setBrush(Qt::black);
		painter->drawRect(QRect(-12, -12, scoreWidth + 4, scoreHeight + 4));

		//combo and score
		{
			painter->scale(1.0, -1.0);


			painter->setPen(comboBarColor);
			painter->drawText(0, 0, ("[COMBO]  " + std::to_string(combo)).c_str());


			painter->setPen(scoreBarColor);
			painter->drawText(0, -scoreFontSize - 5, ("[SCORE]  " + std::to_string(scoreDisplaying)).c_str());

			painter->scale(1.0, -1.0);
		}

		painter->setPen(Qt::black);
		painter->setBrush(Qt::black);
		painter->drawRect(QRect(scoreWidth - 2, -12, Def::trackWidth - scoreWidth - 10 + 4, scoreHeight + 4));

		//hp
		{
			painter->scale(1.0, -1.0);
			painter->setPen(healthBarColor);
			painter->drawText(scoreWidth + 10, -scoreFontSize - 5, ("[HP]  " + std::to_string(health)).c_str());
			painter->drawText(scoreWidth + 130, -scoreFontSize - 5, (" / " + std::to_string(Def::maxHealth)).c_str());
		}

		//fever bar
		{
			double feverFactor = double(fever) / Def::maxFever;

			QPen pen(feverBarColor);
			pen.setWidth(3);
			painter->setPen(pen);
			painter->drawText(scoreWidth + 10, 0, "[FEVER] ");
			for (int i = 0; i < 5; i++)
			{
				painter->setBrush(Qt::black);
				painter->drawRect(scoreWidth + 120 + i * 25, 0, 20, -20);
				painter->setBrush(feverBarColor);
				painter->drawRect(scoreWidth + 120 + i * 25, 0, 20, -20 * std::min(1.0, feverFactor * 5.0));
				feverFactor = std::max(0.0, feverFactor -= 0.2);
			}
			painter->setPen(Qt::black);
		}

		painter->scale(1.0, -1.0);

		painter->translate(-Def::scorePosX, -Def::scorePosY);
	}

	//draw interface
	{
		painter->scale(1.0, -1.0);
		painter->drawImage(QPoint(0, -Def::windowHeight), *interfaceImage);
		painter->scale(1.0, -1.0);
	}

	//draw keyboard
	{
		QFont font = painter->font();
		int fontSize = Def::keySize * 0.7;
		font.setPixelSize(fontSize);
		font.setBold(true);
		painter->setFont(font);
		painter->setPen(Qt::black);

		for (char ch = 'a'; ch <= 'z'; ch++)
		{
			painter->translate(GetKeyPosX(ch), GetKeyPosY(ch));

			painter->scale(1.0, -1.0);
			painter->setBrush(Qt::gray);
			painter->drawImage(QRect(-Def::keySize / 2, -Def::keySize / 2, Def::keySize, -Def::keySize), keyHolding[Ch2QKey(ch)] ? *keyDownImage : *keyImage);
			painter->setBrush(Qt::black);
			painter->scale(1.0, -1.0);

			QString text(1, toupper(ch));
			QFontMetrics m(painter->font());
			int fontSizeX = m.width(text);
			int fontSizeY = m.height();

			painter->scale(1.0, -1.0);
			int keyDownOffset = keyHolding[Ch2QKey(ch)] ? 1 : 0;
			painter->setPen(keyColor[ch]);
			painter->drawText(-fontSizeX / 2 + keyDownOffset, fontSizeY / 2 - 5 + keyDownOffset, text);
			painter->scale(1.0, -1.0);

			painter->translate(-GetKeyPosX(ch), -GetKeyPosY(ch));
		}
	}
}
