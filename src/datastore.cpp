#include "datastore.h"
#include <iostream>

using namespace std;
using namespace xercesc;

Datastore::Datastore()
{
	try
	{
		XMLPlatformUtils::Initialize();
	}
	catch (const XMLException &toCatch)
	{
		char *message = XMLString::transcode(toCatch.getMessage());
		cout << "Error during initialization:\n"
		     << message << endl;
		XMLString::release(&message);
		return;
	}

	m_parser = new XercesDOMParser();
	m_parser->setValidationScheme(XercesDOMParser::Val_Always);
	m_parser->setDoNamespaces(true);    // optional
	m_errorHandler = (ErrorHandler *) new HandlerBase();
	m_parser->setErrorHandler(m_errorHandler);

	m_document = NULL;
}

DOMNode *Datastore::get(const char *xpath)
{
	XMLCh *path = XMLString::transcode(xpath);
	DOMNode *node = get(path);
	XMLString::release(&path);

	return node;
}

DOMNode *Datastore::get(const XMLCh *xpath)
{
	return m_document->getElementsByTagName(xpath)->item(0);
}

int Datastore::load(const char *filename)
{
	try
	{
		m_parser->parse(filename);
		m_document = m_parser->getDocument();
		cout << "Loaded!" << endl;
	}
	catch (const XMLException &toCatch)
	{
		char *message = XMLString::transcode(toCatch.getMessage());
		cout << "Exception message is:" << endl
		     << message << endl;
		XMLString::release(&message);
		return -1;
	}
	catch (const DOMException &toCatch)
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

	return 0;
}

Datastore::~Datastore()
{
	delete m_parser;
	delete m_errorHandler;
	XMLPlatformUtils::Terminate();
}

