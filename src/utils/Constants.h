#ifndef CONSTANTS_H
#define CONSTANTS_H

namespace TE
{
    // Hard coded constants of the app
    namespace Constants
    {
        //hard coded files or directories names
        static constexpr const char* app_lock_file = "AstaCMS.lock";
        static constexpr const char* app_log_file = "AstaCMS";
        static constexpr const char* app_log_file_extension = "txt";
        static constexpr const char* updater_app_log_file = "te_updater.log";
        static constexpr const char* app_config_file = "AstaCMS.conf.ini";
        static constexpr const char* app_session_file = "AstaCMS.session.json";
        static constexpr const char* streams_logs_dir = "streams_logs";
        static constexpr const char* streams_thumbnails_dir = "streams_thumbnails";

        // hard coded messages
        static constexpr const char* areYouSureToexitThisDialogMessage = "Are you sure to exit this dialog?";
        static constexpr const char* cannotCloseThisDialogMessage = "Cannot close this dialog!";
        static constexpr const char* somethingWentWrongMessage = "Something went wrong!";
        static constexpr const char* doYouWantToSaveThisXMessage = "Do you want to save this %1!";

        // hard coded gui css styles
        static constexpr const char* processRunningStyleSheet =
                "border-radius: 10px;\n"
                "min-height: 20px;\n"
                "min-width: 20px;\n"
                "background-color: rgb(70, 211, 0);\n";

        static constexpr const char* processWithProblemStyleSheet =
                "border-radius: 10px;\n"
                "min-height: 20px;\n"
                "min-width: 20px;\n"
                "background-color: rgb(206, 0, 0);\n";

        static constexpr const char* processNotRunningStyleSheet =
                "border-radius: 10px;\n"
                "min-height: 20px;\n"
                "min-width: 20px;\n"
                "background-color: rgb(144, 144, 144);\n";

        static constexpr const char* processStartingStyleSheet =
                "border-radius: 10px;\n"
                "min-height: 20px;\n"
                "min-width: 20px;\n"
                "background-color: rgb(223, 117, 42);\n";

        static const int imageCaptureTimeInterval       = 13000;    //in ms
        static const int speedTestTimerInterval         = 60;       //in mins
        static const int dataPushTimeInterval           = 10;       //in mins
        static const int oneHourTimeIntervalInMinutes   = 60;       //in mins
        static const int twoHourTimeIntervalInMinutes   = 120;       //in mins
        static const int antivirusCheckInMinutes        = 2;        //in mins
        static const int retryLoginInterval             = 5;        //in mins
        static const int oneDayTimeIntervalInSeconds    = 86400;    //in seconds
        static const int sixHoursTimeIntervalInSeconds  = 21600;    //in seconds
        static const int noOfDaysToDeleteLogs           = 1;        //in days
        static const int allowedFolderCount             = 2;
        static const int noOfSecsForOneDay              = 86400;    //in seconds
        static const int bytes                          = 1024;
        static const int appQuitTimeInSeconds           = 2;        //in seconds
        static const int zipFileCountTimerInMins        = 59;       //in mins
        static const int lazyLoadBaseImageTimerInterval = 1;        //in mins
        static const int restartStreamInMins            = 30;       //in mins
        static const int maxAllowedSizeOfFolder         = 90;       //in MB
        static const int minAvailableStorage            = 25;       //in Percentage
        static const int edgeAppGetConfigsThreeMins      = 3;        //in mins
        static const int halfAnHourTimeIntInMinutes     = 30;       //in mins
        static const int sendCameraPreviewAfterLogin    = 5;       //in mins
        static const int checkPreRequisiteConfigsInMins = 1;        //in mins
        static const int extractCameraIPsAfterLogin     = 5;        //in mins
        static const long gigaBytes                     = 1000000000;
        static const int  edgeAppGetConfigsFifteenMins  = 15;       //in mins
        static const int  checkResetRegeditInMins       = 10;       //in mins
        static const int aliveTimer                     = 1;       //in mins
        static const int socketReconnectTime            = 1;       //in mins
        static const int noOfDaysToDeleteEyeTestVideos  = 0;        //in days

        //we might need to make those as parameters not constants
        // amazon kinesis video streaming credentials:

    #if 0 //dev with wrong keys
        static constexpr const char* S3_key_id = "14f7d344c953bfd34c8d482c66053bd783139831";
        static constexpr const char* S3_secret_key = "lDmLgkCKEkMoA+8WXCEs/pyHCgeqcBsWBZlo6W67rdQ=";
        static constexpr const char* kvs_region = "us-ashburn-1";
        static constexpr const char* bucketName = "tango-retail-edge-sdk-dev";
        static constexpr const char* sse_key_id = "3654cce0-9b35-462c-9da8-26c3a8af6d84";


        //rest api path
        static constexpr const char * api_root = "https://70ygi6rjod.execute-api.us-east-1.amazonaws.com/prod";
        static constexpr const char *  XAPIKEY = "KT0RPwR5YEaEMCpIxWvWI9CJKXUyXZJ491XZG5a1";
    #else //prod
        static constexpr const char* S3_key_id = "";
        static constexpr const char* S3_secret_key = "";
        static constexpr const char* kvs_region = "ap-south-1";
        static constexpr const char* bucketName = "AstaCMS-retail-edge-sdk-oracle";
        static constexpr const char* endPointUrl = "https://s3.ap-south-1.amazonaws.com";
        static constexpr const char* sse_key_id = "3654cce0-9b35-462c-9da8-26c3a8af6d84";

        //rest api path
        static constexpr const char * api_root = "https://streamer.AstaCMS.ai";
        static constexpr const char *  XAPIKEY = "KT0RPwR5YEaEMCpIxWvWI9CJKXUyXZJ491XZG5a1";
    #endif

        //#ifdef WIN32 third party executables relative path: relative to the app exe directory.
        static constexpr const char *  gstreamer_exe = "st-launch-1.0.exe";
        static constexpr const char *  s3upload_exe = "s3upload.exe";
        static constexpr const char *  ffmpeg_exe = "ffmpeg.exe";
        //#endif

        // rtspUrl construction skeliton
        static constexpr const char *  rtsp_Hikvision   = "rtsp://#userName#:#password#@#ipAddress#/streaming/channels/#cameranumber#0#quality#";
        static constexpr const char *  rtsp_Panasonic   = "rtsp://#userName#:#password#@#ipAddress#/cam/realmonitor?channel=#cameranumber#&subtype=#quality#";
        static constexpr const char *  rtsp_Matrix      = "rtsp://#userName#:#password#@#ipAddress#/unicaststream/1";
        static constexpr const char *  rtsp_CP_plus     = "rtsp://#userName#:#password#@#ipAddress#/cam/realmonitor?channel=#cameranumber#&subtype=#quality#";
        // gstreamer cli string patern
        // #RTSPURL# : rtsp url : stream url
        // #STREAM_NAME# : stream-name obtained with add camera api call
        // #AK# : acces-key : hard coded , distributed with the app
        // #SK# : secret key : hard coded , distributed with the app
        // #REGION# : aws-region : hard coded , distributed with the app
        // #RP# : retention period (ushort)
    #define TEST_VIDEO_SRC 0
    #if !TEST_VIDEO_SRC
        static constexpr const char *  streamer_cli_pattern = " rtspsrc location=\"#RTSPURL#\" ! "
                                                              " rtph264depay ! h264parse !  video/x-h264, stream-format=avc,alignment=au ! "
                                                              " kvssink stream-name=\"#STREAM_NAME#\" "
                                                              " storage-size=512 access-key=\"#AK#\" secret-key=\"#SK#\" aws-region=\"#REGION#\" "
                                                              " framerate=1 retention-period=#RP# ";

        static constexpr const char *  s3Upload_cli_pattern = "#OBJPATH# #OBJNAME# #ACSKEY# #SECKEY# #REGION# #EPURL# #BUCKET#";

    #else
        static constexpr const char *  test_video_src = "v "
                                                        "ideotestsrc is-live=true ! openh264enc";
        static constexpr const char *  streamer_cli_pattern = " #RTSPURL# ! "
                                                              " h264parse !  video/x-h264, stream-format=avc,alignment=au ! "
                                                              " kvssink stream-name=\"#STREAM_NAME#\" "
                                                              " storage-size=512 access-key=\"#AK#\" secret-key=\"#SK#\" aws-region=\"#REGION#\" "
                                                              " framerate =1 retention-period=#RP# ";
    #endif
        // FFMPEG snapshooter cli command pattern.
        // %1 url
        // %2 snapshot file
        static constexpr const char * ffmpeg_args="-y -rtsp_transport tcp -i %1 -frames:v 1 %2";


        //TODO  separate the KP-SDK-RUN time and the app installer
        static constexpr const char* KinesisVideoStreamsProducerRuntimeUrl="";
        static int LoadingStreamWaitTime = 5000; // 60 secs

        static constexpr const char* logBucket = "edgeapp-logs";

//        static constexpr const char * modern_api_root        = "https://edgeapp.AstaCMS.ai/v5";

        static constexpr const char * astaCMSApp_server         = "https://edgeapp.AstaCMS.ai";
//        static constexpr const char * modern_api_root        = "https://edgeappweb.AstaCMS.ai/v6";
        static constexpr const char * modern_api_root        = "https://edgeapptest.AstaCMS.ai/v6";
        static constexpr const char * websocket_route        = "https://eyetesttest.AstaCMS.ai/v1";
        static constexpr const char * websocket_server       = "ws://eyetest.AstaCMS.ai";
        static constexpr const char * eyeTestDataUpload      = "eyeTest/dataupload";
        static constexpr const char * xAPIKeyHeader          = "X-API-KEY";
        static constexpr const char * edgeAppAuthHedaer      = "edgeapp-authorization";
        static constexpr const char * contentTypeJson        = "application/json";
        static constexpr const char * speedTestFileName      = "10mb.zip";
        static constexpr const char * loginRoute             = "edgeapp/login";
        static constexpr const char * checkUpdateRoute       = "edgeapp/appversion";
        static constexpr const char * resetRegeditRoute      = "edgeapp/reset";
        static constexpr const char * dataUploadRoute        = "edgeapp/dataupload";
        static constexpr const char * edgeAppConfigRoute     = "dashboard/edgeapp/config";
        static constexpr const char * getManufacturerRoute   = "edgeapp/getmanufacture";
        static constexpr const char * dataLogUploadRoute     = "edgeapp/datalogupload";
        static constexpr const char * logsToDBRoute          = "edgeapp/applicationlogs";
        static constexpr const char * macAddressFileName     = "\\macaddress.io-db.xls";
        static constexpr const char * bytesPerSecond         = "bytes/sec";
        static constexpr const char * kiloBytesPerSecond     = "KB/sec";
        static constexpr const char * megaBytesPerSecond     = "MB/sec";
        static constexpr const char * defaultDataLocation    = "c:/";
        static constexpr const char * getIpListRoute         = "edgeapp/iplist";

        static constexpr const char * preRequisiteRoute           = "edgeapp/prerequisite";
        static constexpr const char * preRequisitDataRoute        = "edgeapp/prerequisite/data";
        static constexpr const char * preRequisitDataUploadRoute  = "edgeapp/prerequisite/dataupload";

        static constexpr const char * cameraPreviewBaseImageRoute = "edgeapp/baseImage";

    }
}
#endif // CONSTANTS_H
