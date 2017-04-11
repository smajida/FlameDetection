#include "Config.h"
#include "qdir.h"

CConfig::CConfig()
{    
    LoadXmlFile();
}

void CConfig::LoadXmlFile()
{
    if (!QDir(CONF_PATH).exists())
        QDir().mkdir(CONF_PATH);

    CvFileStorage* fs = NULL;

    try
    {
        fs = cvOpenFileStorage(XML_FILE, 0, CV_STORAGE_READ);
    }
    catch (...)
    {
        setDefault();
        return;
    }


    if (fs == NULL)
    {
        setDefault();
        return;
    }

    _config.frmPosX             = cvReadIntByName(fs, 0, "FrmPosX", 0);
    _config.frmPosY             = cvReadIntByName(fs, 0, "FrmPosY", 0);
    _config.frmWidth            = cvReadIntByName(fs, 0, "FrmWidth", 800);
    _config.frmHeight           = cvReadIntByName(fs, 0, "FrmHeight", 600);
    _config.strCamUrl           = cvReadStringByName(fs, 0, "CamUrl", "udp://@192.168.150.182:15006");

    cvReleaseFileStorage(&fs);
}

void CConfig::setDefault()
{    
    _config.frmPosX         = 0;
    _config.frmPosY         = 0;
    _config.frmWidth        = 800;
    _config.frmHeight       = 600;
    _config.strCamUrl       = "udp://@192.168.150.182:15006";

    SaveXmlFile();    
}



void CConfig::SaveXmlFile()
{
    CvFileStorage* fs = cvOpenFileStorage(XML_FILE, 0, CV_STORAGE_WRITE);

    cvWriteString(fs, "VsCamGV", _config.strCamUrl.data());
    cvWriteInt(fs, "FrmPosX", _config.frmPosX);
    cvWriteInt(fs, "FrmPosY", _config.frmPosY);
    cvWriteInt(fs, "FrmWidth", _config.frmWidth);
    cvWriteInt(fs, "FrmHeight", _config.frmHeight);

    cvReleaseFileStorage(&fs);
}