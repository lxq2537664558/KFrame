#ifndef __KF_HTTP_H__
#define __KF_HTTP_H__

#include "KFrame.h"

namespace KFrame
{
	class KFHttp
	{
	public:
		KFHttp();
		virtual ~KFHttp();
		
		// 执行http访问
		virtual std::string RunHttp( const std::string& url, const std::string& data );

	protected:
		// 获得访问路径
		virtual std::string GetURI( const std::string& url, Poco::URI& pocouri );

		// 请求访问
		virtual std::string HttpRequest( Poco::Net::HTTPRequest& request, Poco::URI& url, const std::string& data );

		// 获得clientsession
		virtual Poco::Net::HTTPClientSession* GetHttpSession() = 0;
		//////////////////////////////////////////////////////////////////////////////////////
	};

}
#endif 

