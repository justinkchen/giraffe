#ifndef _PROJECTGIRAFFE_FRAME_H_
#define _PROJECTGIRAFFE_FRAME_H_

#include <FBase.h>
#include <FUi.h>


class ProjectGiraffeFrame
	: public Tizen::Ui::Controls::Frame
{
public:
	ProjectGiraffeFrame(void);
	virtual ~ProjectGiraffeFrame(void);

public:
	virtual result OnInitializing(void);
	virtual result OnTerminating(void);
};

#endif	//_PROJECTGIRAFFE_FRAME_H_
