/*
 * Licensed to the Apache Software Foundation (ASF) under one or more
 * contributor license agreements.  See the NOTICE file distributed with
 * this work for additional information regarding copyright ownership.
 * The ASF licenses this file to You under the Apache License, Version 2.0
 * (the "License"); you may not use this file except in compliance with
 * the License.  You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include <xercesc/parsers/XercesDOMParser.hpp>
#include <xercesc/dom/DOM.hpp>
#include <xercesc/sax/HandlerBase.hpp>
#include <xercesc/util/XMLString.hpp>
#include <xercesc/util/PlatformUtils.hpp>

#include <iostream>

using namespace std;
using namespace xercesc;

void f();
void f()
{
	cout << "A quick brown fox..." << endl;
}

int main(int argc, char* argv[])
{
    if (argc <= 1)
    {
        cout << "Usage: " << argv[0] << " <xml file>" << endl;
        return 1;
    }

    try
    {
        XMLPlatformUtils::Initialize();
    }
    catch (const XMLException& toCatch)
    {
        char *message = XMLString::transcode(toCatch.getMessage());
        cout << "Error during initialization! :\n"
             << message << endl;
        XMLString::release(&message);
        return 1;
    }

    XercesDOMParser *parser = new XercesDOMParser();
    parser->setValidationScheme(XercesDOMParser::Val_Always);
    parser->setDoNamespaces(true);    // optional

    ErrorHandler *errHandler = (ErrorHandler*) new HandlerBase();
    parser->setErrorHandler(errHandler);

    char *xmlFile = argv[1];

    try
    {
        parser->parse(xmlFile);
    }
    catch (const XMLException& toCatch)
    {
        char *message = XMLString::transcode(toCatch.getMessage());
        cout << "Exception message is:" << endl
             << message << endl;
        XMLString::release(&message);
        return -1;
    }
    catch (const DOMException& toCatch)
    {
        char *message = XMLString::transcode(toCatch.msg);
        cout << "Exception message is:" << endl
             << message << endl;
        XMLString::release(&message);
        return -1;
    }
    catch (...)
    {
        cout << "Unexpected Exception" << endl ;
        return -1;
    }

    DOMDocument *document = parser->getDocument();

    XMLCh *bb = XMLString::transcode("black-book");
	XMLCh *fname = XMLString::transcode("f");

	DOMNode *bbNode = document->getElementsByTagName(bb)->item(0);
	bbNode->setUserData(fname, (void *)f, NULL);
    char *tc = XMLString::transcode(bbNode->getTextContent());
    cout <<  tc << endl;

	((void (*)())(bbNode->getUserData(fname)))(); // call f() from user data

    XMLString::release(&bb);
    XMLString::release(&tc);
	XMLString::release(&fname);

    cout << "Parsed!" << endl;

    delete parser;
    delete errHandler;

    XMLPlatformUtils::Terminate();
    return 0;
}
