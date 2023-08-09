#ifndef LANGUAGESELECTORELEMENT_HPP
#define LANGUAGESELECTORELEMENT_HPP

#include <gui_generated/containers/languageSelectorElementBase.hpp>
#include <BitmapDatabase.hpp>
#include <texts/TextKeysAndLanguages.hpp>

class languageSelectorElement : public languageSelectorElementBase
{
public:
    languageSelectorElement();
    virtual ~languageSelectorElement() {}

    virtual void initialize();

	void setupElement(BitmapId bmpID, TEXTS text);
protected:
};

#endif // LANGUAGESELECTORELEMENT_HPP
