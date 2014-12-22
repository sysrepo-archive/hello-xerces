#ifndef __DSNODE_H__
#define __DSNODE_H__

#include <xercesc/parsers/XercesDOMParser.hpp>
#include <xercesc/dom/DOM.hpp>
#include <xercesc/sax/HandlerBase.hpp>
#include <xercesc/util/PlatformUtils.hpp>
#include <xercesc/util/XMLString.hpp>

using namespace xercesc;

class DSNode : DOMNode
{
	public:
		DSNode();
		~DSNode();

	protected:
};

#endif // __DSNODE_H__
