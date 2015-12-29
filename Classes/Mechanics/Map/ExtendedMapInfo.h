#pragma once

#include "cocos2d.h"
namespace HexGame
{
	class ExtendedMap;
	class ExtendedMapInfo : public cocos2d::Ref, public cocos2d::SAXDelegator
	{
	private:
		std::string m_sCurrentString;
		ExtendedMap*				m_pExtendedMap;
	public:
		ExtendedMapInfo();
		virtual ~ExtendedMapInfo();

		static ExtendedMapInfo* create(const std::string& mapFile, ExtendedMap* extendedMap);
		bool initWithTMXFile(const std::string& mapFile);
		bool parseXMLFile(const std::string& xmlFilename);

		void setExtendedMap(ExtendedMap* extendedMap);

		// the XML parser calls here with all the elements
		void startElement(void *ctx, const char *name, const char **atts);
		void endElement(void *ctx, const char *name);
		void textHandler(void *ctx, const char *ch, int len);
	};
}

