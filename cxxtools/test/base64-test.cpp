/*
 * Copyright (C) 2010 Tommi Maekitalo
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

#include <iostream>
#include "cxxtools/base64stream.h"
#include "cxxtools/unit/testsuite.h"
#include "cxxtools/unit/registertest.h"

class Base64Test : public cxxtools::unit::TestSuite
{
    public:
        Base64Test()
        : cxxtools::unit::TestSuite("base64")
        {
            registerMethod("encodeTest0", *this, &Base64Test::encodeTest0);
            registerMethod("encodeTest1", *this, &Base64Test::encodeTest1);
            registerMethod("encodeTest2", *this, &Base64Test::encodeTest2);
            registerMethod("encodeDecodeTest", *this, &Base64Test::encodeDecodeTest);
            registerMethod("binaryTest", *this, &Base64Test::binaryTest);
        }

        void encodeTest0()
        {
            std::ostringstream s;
            
            cxxtools::Base64ostream encoder(s);
            encoder << "123456789";
            encoder.terminate();

            CXXTOOLS_UNIT_ASSERT_EQUALS(s.str(), "MTIzNDU2Nzg5");
        }

        void encodeTest1()
        {
            std::ostringstream s;
            
            cxxtools::Base64ostream encoder(s);
            encoder << "1234567890";
            encoder.terminate();

            CXXTOOLS_UNIT_ASSERT_EQUALS(s.str(), "MTIzNDU2Nzg5MA==");
        }

        void encodeTest2()
        {
            std::ostringstream s;

            cxxtools::Base64ostream encoder(s);
            encoder << "12345678901";
            encoder.terminate();

            CXXTOOLS_UNIT_ASSERT_EQUALS(s.str(), "MTIzNDU2Nzg5MDE=");
        }

        void encodeDecodeTest()
        {
            std::string data;
            for (unsigned n = 0; n < 100; ++n)
            {
                data += static_cast<char>('0' + n%10);
                for (char c = 'A'; c <= 'Z'; ++c)
                    data += c;
                data += '\n';
            }

            std::stringstream s;
            cxxtools::Base64ostream encoder(s);
            encoder << data;
            encoder.end();

            std::ostringstream s2;
            cxxtools::Base64istream decoder(s);
            s2 << decoder.rdbuf();
            std::string data2(s2.str());

            CXXTOOLS_UNIT_ASSERT_EQUALS(data, data2);
        }

        void binaryTest()
        {
            std::stringstream s;
            std::string data("\xff\xd8\xff\xe0\x00\x10\x4a\x46\x00\x01\x01\x00\x48", 16);

            cxxtools::Base64ostream encoder(s);
            encoder << data;
            encoder.terminate();

            std::ostringstream s2;
            cxxtools::Base64istream decoder(s);
            s2 << decoder.rdbuf();
            std::string data2(s2.str());

            CXXTOOLS_UNIT_ASSERT_EQUALS(data, data2);
        }

};

cxxtools::unit::RegisterTest<Base64Test> register_Base64Test;
