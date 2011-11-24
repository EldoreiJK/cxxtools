/*
 * Copyright (C) 2011 Tommi Maekitalo
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

#include <cxxtools/bin/rpcserver.h>
#include "rpcserverimpl.h"

namespace cxxtools
{
namespace bin
{
RpcServer::RpcServer(EventLoopBase& eventLoop)
    : _impl(new RpcServerImpl(eventLoop, runmodeChanged))
{ }

RpcServer::RpcServer(EventLoopBase& eventLoop, const std::string& ip, unsigned short int port, int backlog)
    : _impl(new RpcServerImpl(eventLoop, runmodeChanged))
{
    listen(ip, port, backlog);
}

RpcServer::~RpcServer()
{
    delete _impl;
}

ServiceProcedure* RpcServer::getProcedure(const std::string& name)
{
    return _impl->getProcedure(name);
}

void RpcServer::releaseProcedure(ServiceProcedure* proc)
{
    return _impl->releaseProcedure(proc);
}

void RpcServer::registerProcedure(const std::string& name, ServiceProcedure* proc)
{
    _impl->registerProcedure(name, proc);
}

void RpcServer::listen(const std::string& ip, unsigned short int port, int backlog)
{
    _impl->listen(ip, port, backlog);
}

unsigned RpcServer::minThreads() const
{
    return _impl->minThreads();
}

void RpcServer::minThreads(unsigned m)
{
    _impl->minThreads(m);
}

unsigned RpcServer::maxThreads() const
{
    return _impl->maxThreads();
}

void RpcServer::maxThreads(unsigned m)
{
    _impl->maxThreads(m);
}

std::size_t RpcServer::idleTimeout() const
{
    return _impl->idleTimeout();
}

void RpcServer::idleTimeout(std::size_t m)
{
    _impl->idleTimeout(m);
}


}
}
