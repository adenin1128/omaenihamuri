#include <DxLib.h>
#include "Trigger.h"
#include "time.h"

namespace KeyBuffer
{
    static const float REPEAT_TIME = 0.5f;      //  �L�[���s�[�g�Ԋu(sec)

    static bool triggerKeyBufferArray[0xff];    //  �g���K�[�L�[�o�b�t�@
}


/**********************/
/***    KeyUtility  ***/
/**********************/

//  �L�[�֘A�����̏�����
void KeyTrigger::Init()
{
    for (int i = 0; i < 0xff; i++)
    {
        KeyBuffer::triggerKeyBufferArray[i] = false;
    }
}

//  �L�[���͂̃g���K�[�擾
bool KeyTrigger::CheckTrigger(int keyCode)
{
    bool triggerFlag = false;

    //  �Y���L�[��������Ă���
    if (CheckHitKey(keyCode) != 0)
    {
        //  �O�t���[���ŉ�����Ă��Ȃ��������g���K�[
        if (!KeyBuffer::triggerKeyBufferArray[keyCode])
        {
            triggerFlag = true;
        }
        //�L�[�o�b�t�@�ɓo�^
        KeyBuffer::triggerKeyBufferArray[keyCode] = true;
    }
    else
    {
        //�L�[�o�b�t�@�ɓo�^
        KeyBuffer::triggerKeyBufferArray[keyCode] = false;
    }

    return triggerFlag;
}