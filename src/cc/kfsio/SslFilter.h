//---------------------------------------------------------- -*- Mode: C++ -*-
// $Id$
//
// Created 2013/06/24
// Author:  Mike Ovsiannikov 
//
// Copyright 2013 Quantcast Corp.
//
// This file is part of Kosmos File System (KFS).
//
// Licensed under the Apache License, Version 2.0
// (the "License"); you may not use this file except in compliance with
// the License. You may obtain a copy of the License at
//
// http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or
// implied. See the License for the specific language governing
// permissions and limitations under the License.
//
// \brief Ssl socket layer implementation.
//
//----------------------------------------------------------------------------

#ifndef KFS_IO_SSL_FILTER_H
#define KFS_IO_SSL_FILTER_H

#include "NetConnection.h"
#include <string>

namespace KFS
{
using std::string;

class Properties;
class TcpSocket;

class SslFilter : public NetConnection::Filter
{
public:
    class Ctx;
    typedef unsigned long Error;

    static Error Initialize();
    static Error Cleanup();
    static string GetErrorMsg(
        Error inError);

    static Ctx* CreateCtx(
        const char*       inParamsPrefixPtr,
        const Properties& inParams);

    SslFilter(
        Ctx& inCtx);
    Error GetError() const;
    virtual ~SslFilter();
    virtual bool WantRead(
        const NetConnection& inConnection) const;
    virtual bool WantWrite(
        const NetConnection& inConnection) const;
    virtual int Read(
        NetConnection& inConnection,
        TcpSocket&     inSocket,
        IOBuffer&      inIoBuffer,
        int            inMaxRead);
    virtual int Write(
        NetConnection& inConnection,
        TcpSocket&     inSocket,
        IOBuffer&      inIoBuffer);
    virtual void Close(
        NetConnection& inConnection,
        TcpSocket*     inSocketPtr);
    virtual void Attach(
        NetConnection& inConnection,
        TcpSocket*     inSocketPtr);
    virtual void Detach(
        NetConnection& inConnection,
        TcpSocket*     inSocketPtr);
private:
    class Impl;
    Impl& mImpl;
private:
    SslFilter(
        const SslFilter& inFilter);
    SslFilter& operator=(
        const SslFilter& inFilter);
};

}

#endif /* KFS_IO_SSL_FILTER_H */