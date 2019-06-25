﻿
#include "KFrame.h"
//////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////
#if __KF_SYSTEM__ == __KF_WIN__
    //////////////////////////////////////////////////////////////////////////////////////////////////
    #ifdef __KF_DEBUG__
        #pragma comment( lib, "KFExceld.lib" )
        #pragma comment( lib, "KFUtilityd.lib" )

    #endif
    //////////////////////////////////////////////////////////////////////////////////////////////////
    #ifdef __KF_RELEASE__
        #pragma comment( lib, "KFExcel.lib" )
        #pragma comment( lib, "KFUtility.lib" )
    #endif
    //////////////////////////////////////////////////////////////////////////////////////////////////
#endif

#include "KFParse.h"
using namespace KFrame;

void Parse( int argc, char* argv[] )
{
    if ( argc < 3 )
    {
        std::cout << "Param Error!" << std::endl;
        return;
    }

    std::string excelfile = argv[ 1 ];
    uint32 saveflag = atoi( argv[ 2 ] );
    std::cout << "Start Parse Excel File = " << excelfile << "!" << std::endl;

    bool load = _kf_parse->LoadFromExcel( excelfile.c_str(), true );
    if ( !load )
    {
        std::cout << "Load File = " << excelfile << " Failed!" << std::endl;
        return;
    }


    for ( auto i = 3; i < argc; ++i )
    {
        std::string param = argv[ i ];

        auto prefix = KFUtility::SplitString( param, "=" );
        auto path = param;

        if ( prefix == "--xml" )
        {
            _kf_parse->SaveToXml( path.c_str(), saveflag );
        }
        else if ( prefix == "--csv" )
        {
            _kf_parse->SaveToCSV( path.c_str() );
        }
        else if ( prefix == "--csharp" )
        {
            _kf_parse->SaveToCSharp( path.c_str() );

        }
        else if ( prefix == "--cpp" )
        {
            _kf_parse->SaveToHpp( path.c_str() );
            _kf_parse->SaveToCpp( path.c_str() );
        }
    }

    std::cout << "Parse Excel File = " << excelfile << " OK!" << std::endl;

    ////////////////////////////////////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////////////////////////////////////
}

int main( int argc, char* argv[] )
{
    Parse( argc, argv );
    return 0;
}

