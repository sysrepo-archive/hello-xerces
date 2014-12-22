#ifndef __DATASTORE_H__
#define __DATASTORE_H__

#include <xercesc/parsers/XercesDOMParser.hpp>
#include <xercesc/dom/DOM.hpp>
#include <xercesc/sax/HandlerBase.hpp>
#include <xercesc/util/PlatformUtils.hpp>
#include <xercesc/util/XMLString.hpp>

#include "dsnode.h"

using namespace xercesc;

class Datastore
{
	public:
		Datastore();
		~Datastore();

		void set(const XMLCh *xpath, void *value);
		DOMNode *get(const XMLCh *xpath);
		DOMNode *get(const char *xpath);

		void save(const char *filename);
		int load(const char *filename);

	protected:
		XercesDOMParser *m_parser;
		ErrorHandler *m_errorHandler;
		DOMDocument *m_document;
};

#endif // __DATASTORE_H__
