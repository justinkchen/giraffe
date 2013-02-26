#ifndef _HELLOWORLD_FRAME_H_
#define _HELLOWORLD_FRAME_H_

#include <FBase.h>
#include <FUi.h>


class HelloWorldFrame
	: public Tizen::Ui::Controls::Frame
{
public:
	HelloWorldFrame(void);
	virtual ~HelloWorldFrame(void);

public:
	virtual result OnInitializing(void);
	virtual result OnTerminating(void);
};

#endif	//_HELLOWORLD_FRAME_H_
