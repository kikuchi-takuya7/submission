#pragma once
#include "Engine/GameObject.h"
#include "PlayerState/PlayerState.h"


//���������Ǘ�����N���X
class Player : public GameObject
{
    
public:
    //�R���X�g���N�^
    Player(GameObject* parent);

    //�f�X�g���N�^
    ~Player();

    //������
    void Initialize() override;

    //�X�V
    void Update() override;

    //�`��
    void Draw() override;

    //�J��
    void Release() override;

private:

    enum PLAYERSTATE {
        IDLE = 0,
        MOVE,
        ACTION,
        EMOTE
    };

    enum EMOTESTATE {
        APPLAUSE = 0,//����
        BOW,//�����V
        NUM
    };

    PLAYERSTATE currentPlayerState_;
    PLAYERSTATE nextPlayerState_;

    EMOTESTATE currentEmoteState_;
    EMOTESTATE nextEmoteState_;

    int hIdleModel_;
    int hMoveModel_;
    int hAnimeModel_[EMOTESTATE::NUM];

    //�Q�[�����n�܂��Ă���̃t���[����
    int gameFlame_;

    //�A�j���[�V�����Ƃ����n�܂��Ă���̃t���[����
    int animationFlame_;

    //���ꂼ��̃A�j���[�V�����̏I���t���[��
    int idleEndFlame_;
    int moveEndFlame_;
    int applauseEndFlame_;
    int bowEndFlame_;

    //���肪������킹��^�C�~���O�̃t���[��
    int changeApplauseTiming_;

    //�����Ɣ��肳���邽�߂̃t���O
    bool changeApplauseFlag_;

    float totalMouseMoveX_;
    float totalMouseMoveY_;

private:

    //state��ύX
    void ChangePlayerState(PLAYERSTATE nextState);

    //State���̏������Ɖ������
    void OnEnterPlayerState(PLAYERSTATE state);
    void OnLeavePlayerState(PLAYERSTATE state);

    //animationstate��ύX
    void ChangeEmoteState(EMOTESTATE nextState);

    //animationState���̏������Ɖ������
    void OnEnterEmoteState(EMOTESTATE state);
    void OnLeaveEmoteState(EMOTESTATE state);


    void Idle_Update();
    void Move_Update();
    void Action_Update();
    void Emote_Update();
    void Emote_Draw();

    //�Ή�����L�[�������ꂽ�炻��state�ɂ���
    void CheckMoveKey();
    void CheckEmoteKey();
    
    //�G���[�g������ҋ@��Ԃ�
    void ChangeToIdle();

    void Move_Player();
    void Move_Camera();
};