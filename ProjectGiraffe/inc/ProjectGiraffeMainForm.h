#ifndef _PROJECTGIRAFFE_MAIN_FORM_H_
#define _PROJECTGIRAFFE_MAIN_FORM_H_

#include <FBase.h>
#include <FUi.h>


class ProjectGiraffeMainForm
	: public Tizen::Ui::Controls::Form
	, public Tizen::Ui::IActionEventListener
	, public Tizen::Ui::Controls::IFormBackEventListener
{
public:
	ProjectGiraffeMainForm(void);
	virtual ~ProjectGiraffeMainForm(void);
	bool Initialize(void);

public:
	virtual result OnInitializing(void);
	virtual result OnTerminating(void);
	virtual void OnFormBackRequested(Tizen::Ui::Controls::Form& source);
	virtual void OnActionPerformed(const Tizen::Ui::Control& source, int actionId);

protected:
	static const int ID_FOOTER_ITEM1 = 101;
	static const int ID_FOOTER_ITEM2 = 102;
	static const int ID_FOOTER_ITEM3 = 103;
	static const int ID_HEADER_BUTTON = 104;

	int toggleButtonStatus;
};

#endif	//_PROJECTGIRAFFE_MAIN_FORM_H_
