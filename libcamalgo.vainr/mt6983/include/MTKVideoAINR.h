#ifndef _MTK_VIDEOAINR_H
#define _MTK_VIDEOAINR_H

#include "MTKVideoAINRType.h"
#include "MTKVideoAINRErrCode.h"

#define MAX_TILE_NUM 3

typedef enum
{
	VIDEOAINR_FEATURE_GET_VERSION,
	VIDEOAINR_FEATURE_GET_WRKBUF_SIZE,
	VIDEOAINR_FEATURE_SET_WRKBUF_ADDR,
	VIDEOAINR_FEATURE_GET_TILE_INFO,
	VIDEOAINR_FEATURE_GET_WPE_ROI_INFO,
}   VIDEOAINR_FEATURE_ENUM;

typedef enum
{
	VIDEOAINR_WRKBUF_NAME_PROC_WRK_MDLA_G_TILE0,
	VIDEOAINR_WRKBUF_NAME_PROC_WRK_MDLA_G_TILE1,
	VIDEOAINR_WRKBUF_NAME_PROC_WRK_MDLA_G_TILE2,
	VIDEOAINR_WRKBUF_NAME_PROC_WRK_MDLA_RBA_TILE0,
	VIDEOAINR_WRKBUF_NAME_PROC_WRK_MDLA_RBA_TILE1,
	VIDEOAINR_WRKBUF_NAME_PROC_WRK_MDLA_RBA_TILE2,
	VIDEOAINR_WRKBUF_NAME_PROC_WRK_IN_FRC_TILE0,
	VIDEOAINR_WRKBUF_NAME_PROC_WRK_IN_FRC_TILE1,
	VIDEOAINR_WRKBUF_NAME_PROC_WRK_IN_FRC_TILE2,
	VIDEOAINR_WRKBUF_NAME_PROC_WRK_OUT_FRC_TILE0,
	VIDEOAINR_WRKBUF_NAME_PROC_WRK_OUT_FRC_TILE1,
	VIDEOAINR_WRKBUF_NAME_PROC_WRK_OUT_FRC_TILE2,
	VIDEOAINR_WRKBUF_NAME_PROC_WRK_ALPHA_TILE0,
	VIDEOAINR_WRKBUF_NAME_PROC_WRK_ALPHA_TILE1,
	VIDEOAINR_WRKBUF_NAME_PROC_WRK_ALPHA_TILE2,
	VIDEOAINR_WRKBUF_NAME_PROC_WRK_RESIDUAL_TILE0,
	VIDEOAINR_WRKBUF_NAME_PROC_WRK_RESIDUAL_TILE1,
	VIDEOAINR_WRKBUF_NAME_PROC_WRK_RESIDUAL_TILE2,
	VIDEOAINR_WRKBUF_TOTAL_NUMBER
}   VIDEOAINR_WRKBUF_NAME_ENUM;

typedef enum
{
	VIDEOAINR_EXTBUF_NAME_AUXI_IN_DATA,
	VIDEOAINR_EXTBUF_NAME_AUXI_OUT_DATA,
	VIDEOAINR_EXTBUF_NAME_PROC_IN_AUXI,
	VIDEOAINR_EXTBUF_NAME_PROC_IN_FRC,
	VIDEOAINR_EXTBUF_NAME_PROC_IN_CURRENT_G,
	VIDEOAINR_EXTBUF_NAME_PROC_IN_CURRENT_R,
	VIDEOAINR_EXTBUF_NAME_PROC_IN_CURRENT_B,
	VIDEOAINR_EXTBUF_NAME_PROC_IN_PREVIOUS_G,
	VIDEOAINR_EXTBUF_NAME_PROC_IN_PREVIOUS_RB,
	VIDEOAINR_EXTBUF_NAME_PROC_OUT_FRC,
	VIDEOAINR_EXTBUF_NAME_PROC_OUT_RNN_G,
	VIDEOAINR_EXTBUF_NAME_PROC_OUT_RNN_RB,
	VIDEOAINR_EXTBUF_NAME_PROC_OUT_ISP_G,
	VIDEOAINR_EXTBUF_NAME_PROC_OUT_ISP_R,
	VIDEOAINR_EXTBUF_NAME_PROC_OUT_ISP_B,
	VIDEOAINR_EXTBUF_TOTAL_NUMBER
}   VIDEOAINR_EXTBUF_NAME_ENUM;

typedef struct VideoAINRInitInfo
{
	MINT32 imgWidth;
	MINT32 imgHeight;
	MINT32 tileNum; // 1: frame mode, n: n-tile mode
	void* nvram;
} VideoAINRInitInfo;

typedef struct VideoAINRBuf
{
	MUINT32 size;
	void* va;
	MINT32 fd;
	MINT32 offset;
	MINT32 stride;
	VideoAINRBuf()
		:size(0), va(NULL), fd(-1), offset(0), stride(0)
	{}
} VideoAINRBuf;

typedef struct VideoAINRWrkBufInfo
{
	MINT32 num;
	VideoAINRBuf buf[VIDEOAINR_WRKBUF_TOTAL_NUMBER];
} VideoAINRWrkBufInfo;

typedef struct VideoAINRTile
{
	MUINT32 widthStart;
	MUINT32 widthEnd;
	MUINT32 heightStart;
	MUINT32 heightEnd;
} VideoAINRTile;

typedef struct VideoAINRDetailBuf
{
	VIDEOAINR_EXTBUF_NAME_ENUM name;
	MUINT32 size;
	MUINT32 width;
	MUINT32 height;
	MUINT32 channel;
	MINT32 tileNum;
	VideoAINRTile tile[MAX_TILE_NUM];
} VideoAINRDetailBuf;

typedef struct VideoAINRDetailExtBufInfo
{
	MINT32 num;
	VideoAINRDetailBuf buf[VIDEOAINR_EXTBUF_TOTAL_NUMBER];
} VideoAINRDetailExtBufInfo;

typedef struct VideoAINRWPEQueryIn
{
	//int imgWidth;
	//int imgHeight;
	//int overlapSize;
	MUINT32 mapWidth;
	MUINT32 mapHeight;
	MUINT32 tileNum;
	MUINT32 tileIdx;
	MUINT32 alignmentSize;
} VideoAINRWPEQueryIn;

typedef struct VideoAINRWPEROIInfo
{
	MUINT32 X_START;
	MUINT32 Y_START;
	MUINT32 X_END;
	MUINT32 Y_END;
	MUINT32 VGEN_IN_X_START;
	MUINT32 VGEN_IN_Y_START;
	MUINT32 VGEN_HORI_INT_OFST;
	MUINT32 VGEN_VERT_INT_OFST;
	MUINT32 VGEN_HORI_SUB_OFST;
	MUINT32 VGEN_VERT_SUB_OFST;
	MUINT32 VGEN_IN_CROP_W;
	MUINT32 VGEN_IN_CROP_H;
} VideoAINRWPEROIInfo;

typedef struct VideoAINRProcessInput
{
	MUINT32 frameID;
	MUINT32 tileID;
	MUINT32 bypassMDLA;
	VideoAINRBuf inAuxi;
	VideoAINRBuf inFrc;
	VideoAINRBuf inCurrentG;
	VideoAINRBuf inCurrentR;
	VideoAINRBuf inCurrentB;
	VideoAINRBuf inPreviousG;
	VideoAINRBuf inPreviousRB;
	void* nvram;
	void* ndd;
} VideoAINRProcessInput;

typedef struct VideoAINRProcessOutput
{
	MUINT32 frameID;
	MUINT32 tileID;
	VideoAINRBuf outFrc;
	VideoAINRBuf outRnnG;
	VideoAINRBuf outRnnRB;
	VideoAINRBuf outIspG;
	VideoAINRBuf outIspR;
	VideoAINRBuf outIspB;
} VideoAINRProcessOutput;

typedef struct VideoAINRAuxiInput
{
	MUINT32 frameID;
	VideoAINRBuf inData;
    int cropWidth;
	void* nvram;
	void* ndd;
} VideoAINRAuxiInput;

typedef struct VideoAINRAuxiOutput
{
	MUINT32 frameID;
	VideoAINRBuf outData;
} VideoAINRAuxiOutput;

class MTKVideoAINR {
public:
	static MTKVideoAINR *createInstance();
	virtual void destroyInstance(MTKVideoAINR *obj) = 0;
	virtual ~MTKVideoAINR() {}
	virtual MRESULT VideoAINRInit(VideoAINRInitInfo *pParaIn);
	virtual MRESULT VideoAINRFeatureCtrl(MUINT32 FeatureID, void* pParaIn, void* pParaOut);
	virtual MRESULT VideoAINRAuxi(VideoAINRAuxiInput *pParaIn, VideoAINRAuxiOutput *pParaOut);
	virtual MRESULT VideoAINRProcess(VideoAINRProcessInput *pParaIn, VideoAINRProcessOutput *pParaOut);
	virtual MRESULT VideoAINRDeinit();

private:

};
#endif
