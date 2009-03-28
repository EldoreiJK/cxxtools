/*
 * Copyright (C) 2009 by Marc Boris Duerner, Tommi Maekitalo
 * 
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 * 
 * As a special exception, you may use this file as part of a free
 * software library without restriction. Specifically, if other files
 * instantiate templates or use macros or inline functions from this
 * file, or you compile this file and link it with other files to
 * produce an executable, this file does not by itself cause the
 * resulting executable to be covered by the GNU General Public
 * License. This exception does not however invalidate any other
 * reasons why the executable file might be covered by the GNU Library
 * General Public License.
 * 
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 * 
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
 */

#ifndef cxxtools_Net_HttpService_h
#define cxxtools_Net_HttpService_h

#include <cxxtools/mutex.h>
#include <vector>

namespace cxxtools {

namespace net {

class HttpResponder;
class HttpRequest;

class HttpService
{
    public:
        virtual ~HttpService() { }
        virtual HttpResponder* createResponder(const HttpRequest&) = 0;
        virtual void releaseResponder(HttpResponder*) = 0;
};

template <typename ResponderType>
class HttpCachedService : public HttpService
{
        Mutex mutex;
        typedef std::vector<HttpResponder*> Responders;
        Responders responders;

    public:
        ~HttpCachedService()
        {
            for (typename Responders::iterator it = responders.begin(); it != responders.end(); ++it)
                delete *it;
        }

        HttpResponder* createResponder(const HttpRequest& request)
        {
            MutexLock lock(mutex);
            if (responders.empty())
            {
                return new ResponderType(*this);
            }
            else
            {
                HttpResponder* ret = responders.back();
                responders.pop_back();
                return ret;
            }
        }

        void releaseResponder(HttpResponder* resp)
        {
            MutexLock lock(mutex);
            responders.push_back(resp);
        }

};

} // namespace net

} // namespace cxxtools

#endif
