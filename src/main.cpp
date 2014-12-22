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

#include "datastore.h"

#include <iostream>

using namespace std;
using namespace xercesc;

void f();
void f()
{
	cout << "A quick brown fox..." << endl;
}

int main(int argc, char *argv[])
{
	if (argc <= 1)
	{
		cout << "Usage: " << argv[0] << " <xml file>" << endl;
		return 1;
	}

	char *xmlFile = argv[1];

	Datastore datastore;
	datastore.load(xmlFile);

	DOMNode *node = datastore.get("black-book");

	XMLCh *fname = XMLString::transcode("f");

	node->setUserData(fname, (void *)f, NULL);
	char *tc = XMLString::transcode(node->getTextContent());
	cout <<  tc << endl;

	((void ( *)())(node->getUserData(fname)))(); // call f() from user data

	XMLString::release(&tc);
	XMLString::release(&fname);

	return 0;
}
