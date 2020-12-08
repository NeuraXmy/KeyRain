//main.cpp： 程序入口

#include <QtWidgets/qapplication.h>

#include "Application.h"

/**
* KeyRain by NeuraXmy
* 基于Qt的下落式打字游戏
* XMU20级新生C程序设计课程期末大作业
* 项目开始于 2020/11/25
*/

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
   
    Application::GetInstance()->Start();

    return a.exec();
}
























/*------------------------------------------------------------------------------------------------------------------------------------------------
                                                                    .rKMBBBQBBBBBDSr.
                                                              :ugBBBQZ57:       .ijgBBBdr
                                                         .2QBBBgJ:                    :sQBBZ7
                                                     :KBBBRJ.                             .sQBBd:
                                                 .IBBBMr                                      :5BBQ7
                                              :DBBBv                                              rQBBL
                                           :QQBb:                                                    iBQBi
                                        .RBBQi                                                          sBBE.
                     .BBBU            XBBQ:                                                               :QBQ7                .r2
                     gQBBBBE       .BBBr                                                                     jBBu          :5BBBBg
                    :BBBBBBQBL    BBB.                                                                         :BBS      2BBBBBBg
                    BBBBQBQBBBg 7BBr                                                                             .BBv  gBBQBBBBBBgdj:
                7PBBBBBQBQBQBBBBB5  .                             ...                                              :BBBBBBBQBQBBBQBBBBBDr
             vBBBBBBBBQBBBBBBBBBB  .....   .  .              bBBBBBBQBQ        .v2j.                       ......  :BBBBBBBBBBQBBBQBBBBBBB
            BBBBBBBQBBBQBQBQBQBBBK ....:qBBBQ:...          QBBr      :BBBBBQBBQPL:vB1     ................::i::...ZBBBBBBBBQBBBBBBBBBBS: .
            LEQBBBBBBBBBBBQBQBQBBB. iDBBBd:.vB.::iiYJJr. YBB.           ...  BB     YBDi.. ........:.:.:...:..  .BBBBBBBBBQBQBBBBBs.
                 .vdBBBBBBBQBBBBBBQBBDi      sbKq5ZQBBBQBBY   . ... .        LBi      JDRRRMRgRgD7. ..........  BBBQBQBQBQBBBBK.
                      iDBBBBBBBBBBB7                   BB.    ...... . . . .  UB   .     ..::::i7BY...     . . RBBBBBBQBQBQEgB
                          UBBBBBb.    . . ...         BB   .... . ......... .  BB   . .          .EbEXbPqur.  7BBQBQBQBQBBQqRBBBBBBBBBBBBZs.
             .iL1qEQQBgEJi  YBQ.     . ... . ... .   BB    ..... ... . ......  YBi   . . . . .       ..i7XRBQiQBBBBBQBBBBBBBBBQBBBBBBBBBBBBBB2
      iLPQBQBBBBBBBBBQBBBBBBB1      ....... ... .   BB.   ... . ... ..... ...   BB  . . . . . . .           iqBBBQBBBBBQBQBQBBBBBBBBBQBBBQBQB.
      QBBBBBQBBBBBQBBBBBBBBBi     .... ..... ...   MBi   . ......... ... . . .  BB.  . .      .... . . . .     iMBBBQBQBQBQBBBQBBBBBBBQBBBE
       iBBBBBQBBBBBBBQBBBBB.     ...... ... ...   7Qq   . ........... ... . .   PBY   .   iI  ......... . .      2BQBBBQBQBBBQBBBQBQBQBQBQBS
         vBBBBBBBBBBBBBBBB      .... . ... ...    BB   . ......... . . . ... .  JBP  . .  BB   . ..... ... . .   iBBBBBBBBBBBBQBBBQBQBQBQBBBB.
           QBBBQBBBQBBBBB     ... . ... . . .   .QBv  . ..... . . . . .......   7BB   .  sBQ   .... . ... ... .   BBBBBBBBBBBBBBBBBBBBBBBBBBBQ
           IBBQBQBQBBBQB   ..... ..... ... ...  BBB  ... . ... ......... . ...  iBQ.     BQB7  . . . . . . .....  BB:.:iir7s1KdQBBBBBBBBBBQBBBM
           BBBBBBBBBBBB   ... . . .   . . ...  vBBE   .   ... . . ......... .   :BBK    7B uB   ......... ... .   RBP             EB.7PBBBBQBBB
           BBBBBBBgdBd   . ... . .     ... ..  QBBJ      ... . ... . . ...      rBBBi   BB  BB   ... ... . . . .  BBgBBs.         jB     .rgBBQ:
           BBBBBX  BD   ... . . . . uB  . . .  BBQMIu.    ... . .........  .5PP2BB PB   BB   QB:    . ..... ...   BQ .ZQBBM1vi:.  gB          :
           .QI.   BB   . . ... . .  SB.  .     BBBS :ZQ.   ... . ..... . . :v. vBY  BB  QQ    BB:      ........  7BI    .vPBBBBBBBQ5
                 BB   . . . . ...   .B5     Lr RPJB  BBs    ... ..... . .     7BB    UBqBK     BB   .   . ... .  BB.           qB::
                MB.  ........... .   BBr   .BBJKQ BB.BQB:      ..... . .     BBB       5BP     YBi .Bs   . ...  7Bq  ...       vB
               .Bv    ... . .....   KBBQR  PB5BBB: XBB vB5        ...      :BBI         .:     .BX :BP  ... .   BB      ... .  :B
               QB      . . . . ..  .QR 7QBUBB  .71   :  :BQP.            YBBB.                 rBu RBg   .     BB.       ... .  Bv
             :vB7 EB: . . . . . .  5B.   7BBb     .i.     rBBBgr.     uQBBB:  :EEJ:            gB :BBB  .    .BBB1QQBBM7  . .   KQ
           XBBQBIBBB       . ...   BB           uB5r         vBBBBBBBBBB2.      .uR:           BQiBibB    BuXBQ7      QK         B7 .:..
          iBv  BB.iB    r.  ....  iBU               :J.          :YSSi     1BBP.              JBBQi BB    BBL  .::   :Br    rSZK2uBBBBBBBU
          :B.  5X :B   .BB   ...  ZB.   ..:irv1PZBBBBBB.                  .BBBBBBBQBQDSjvvrr:vBBE   Bs   rQ   vLvi   .rBD :QSi.7ZBBBEUr:LBB
          .BB.     B7  7BBB   ..  BB   BBBBBBBBBBBBQBu.                      vEQBBBBBBBQBBBBBQBQP  RB    Bd  :vuEBBQBBBBBBBQ:dBQBr  s.   BM
         .BBJr :   BB  1B BB.     BB  IBBBBBBBBBSr.                                .:7vjuIPggDZQ7 sB:  .BBBBBBQg1r...    .7BBB:  .UQU   .BB
        SBB   .MB7BMBB :B  MBZ    BB                                                             bB.  MQBYi.      L       QZ   :1Sr       2BY
        DB.      .ZB DB.Bi  :BBB: :B                                                           iBR.:BBB.       :ZBB.      Bi   .    :D:    BBr
        7BBU      .Bg iU7.    :PBBKBY                                                      .i2BBBBBB5.   .i7dBBQZ.  .    EB.  . .  vBq    BBBE
       PBZiBBBBBYLQBi  i:       BBi..                                                  .:rIQD5i5QB.    .:7JJvi.    . . .BQ   . .        LBBM.IB1
      BB:    .:.QBB    sBBQSi  IBv                                                      .      BM     .           ...  iBD           iQBBBi   BB
     .QQ        bBB7     .iY:  BB                                                             BB     .           . . .X5 QB.    .7PBBBBv      rBi
     7BP   .v7i. iBBBQv        SB                                           ii                LBBL  .  .gDPPdZgIi .      BBBBBBBBgK7.          :BB:
     5BI     irr  RBDBQBBBBQDZPBBr                                        :gBv                  UB:     :rvJvr:.       2QBqBB: .         SZ    .BBJ
      :BBBBKi   :RBB7  .i7qQBBgUBB:                     .REIv::::...irudBQBE.                   BB                  :bBB: BQ        . .jBB:   UBBZ
       BQ.7QBBQBBBBQggr          dBq                     .vqIu2KSX2UUIj7.                      2BBg2vrii:..:iL2dXi.dBBQBI iBBE:    .  ..    rBBB:
       BB        7BZ              rBB:                                                          .2BBBBBBBBBBBQB2r.      BQ  7BBK          5QBBBQ
      :BB  ZI:.YZBQBY   .XKXIKXU.  :QBB:                                                         XQK:......             BB    QB     .iEBBBD:  BB
       iBBbr7JXRBr BB   .s22SUL:  7BBQBQBd.                                                     XB.               . . rQB     uBBggQBBdq7.     BB
         :QBBq:.BY BBi          vBBBBB jQEBB5.                                                  QB   .  ir::i7rr.     :BB       r7qBD   ijr  :BB.
            :2BBBBurBBBBBQMqPDBBBP. BQ  vd:rBBB5i                                               BB7     JbgDESv.       QB         vBK:     7BBQ
                       7BQsX2Yr:   jBQi: .M2. vBBBgr                                            B2                  .qBB5       P  .BBQuKBBB1
                       dB    uEbI.  .vBB.  iqYdQgQBBBBR2r                                   :IBQBBRdqKK21r. ..ruEBBBBd:Br      iB  BBPPU7.
                       XBK::.  .:7ugBBu        . BQIRBBBBBBBPU7:.               rvrirJPQBBQBBBBgB. BBZIX2Y. .rY2Jr :Q  B.      qBY
                        .uBBBBBBPKBr             :B  .vv:PBiEBBQBBBBBD.        BB5BBg7..BBYSu: .B QB               gB dB       QBQ
                          BQ      B               :B2    QBBSDBB  bB         .BB   BQP.qQv.   .B: QB:::.       .JBBB  B.      RQ.B
                          BBi     BI                .irSBE   EBQ   RQ  .:v2KQQY    BBP 7q17u7YD.   iBBMBg:.iSBBBBs   QP      7B  B.
                          D2B.    LB                 7QBBv   BB7  .BQBBBBP::       QQb     iBBr  QBBBQKDq1sUur      BB      :Bi  B.
                          P7rB     Bj             .KBB:sBBBBgBB: :BBP .RBQ.        BBj       BB7                   BB      :Bv  .B.
                          :B YQ:   :B.        LEBBBBJ  rBBBBBBB2.BQP    vBBBuEMQE2rBB:        BB7.                BB      sBr   iB
                           Q: rB1   rB:      7BB       .BBBQBQBBBBB  :XgBBBBBBBBBBBBB          qqBBBI.          .BB      QB:    qQ
                           vB  .BB.  :BU     UB7        BBQQQBQBQBBBBBBBQBQBQBBBQYBBv  vB.          BBL        UBP     :BB      BP
                            Bi   YBR.  dB:   :BB        rBBQQQBBQBBQBBBQQQBQQQBR rBB   :Bv          BBi      rBB.     BBv      .B
                            :B     1BB:  BP rBjBB       .BBQQQQBQBBBQQBBQBQQQBB  BBi    QB5       .BQB     1QBi     bBd        BQ
                             PB      :ZQ2uBBB   .i7IBBB7uBBQQQBQBBgBBBBQQQBQBBBYBBB     JBU      :EBBQ  sZBu     .MBD         7Q
                              BX        .irBP      :sBBdBBQQRQQBBQ iBBQQQQQQBBBBBB      QBQQbLi7ri.  BQ.:.     YBBU          .Bv
                               Bj          Bs        BE PBBBBQBQBB  BQBQQQQQBDBBBj       sBJBi:       B7    7bBb:            Bq
                                BS         B.        B   BBBQQQBBB  BBBBBBQBB BBB        1B Bi        iBirMB7.             :BK
                                 BM       sB        rB :BBBBBBBBBBR.BBBQBBBBB.MQ         QB QB         7B:                XB7
                                  BB.     Qg        dBgBBBBRBBBQr51BBESSDBBBQZr.         BBQB.          BQ              :BB.
                                   QBErJKXB:        B7       i.                        .PQBP           dB7            .BBv
                                    iBBJYBQ        :Q                                DBBd.            JBi           rBQU
                                  .gBB  BR         Bg      vr                       Bg               ZB:         rBBBi
                                :BBdBQ            .B       BBBs       .            SB             jBBKQQ    .LRBQBP.
                             .JBBY .BQ            BQ       BBBBBZsgQBBB            BBBBg7.        i.:ZBBgr5ZQZ2:
                            sBB.   .QBBBBBBBQRquriB7       BBBBBBBBBQB            .BB 7BBBQBBQJ:   EQB:rBD.
                             1BRq:      .:7J2IPMBBB        BBQBBBQBBQ             .7BL    .7RBBBBBBB1    YQBL
                               .YQBQqsi:.....::YqBg        Ys.   PBQ                iBBU         :         QB.
                                    :71IXSS55j7. 5Bssri..         :.     ..:::rJ5KEgBKsKBB2.          :7PBBQ.
                                                   .:7uXKEEZbdPbqKj5dDZgdd5U7iirrr:.     .LPqKPBQBBBBBBgj:
------------------------------------------------------------------------------------------------------------------------------------------------*/