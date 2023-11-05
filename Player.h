#pragma once
#include "Engine/GameObject.h"
#include "PlayerState/PlayerState.h"


//◆◆◆を管理するクラス
class Player : public GameObject
{
    
public:
    //コンストラクタ
    Player(GameObject* parent);

    //デストラクタ
    ~Player();

    //初期化
    void Initialize() override;

    //更新
    void Update() override;

    //描画
    void Draw() override;

    //開放
    void Release() override;

private:

    enum PLAYERSTATE {
        IDLE = 0,
        MOVE,
        ACTION,
        EMOTE
    };

    enum EMOTESTATE {
        APPLAUSE = 0,//拍手
        BOW,//お辞儀
        NUM
    };

    PLAYERSTATE currentPlayerState_;
    PLAYERSTATE nextPlayerState_;

    EMOTESTATE currentEmoteState_;
    EMOTESTATE nextEmoteState_;

    int hIdleModel_;
    int hMoveModel_;
    int hAnimeModel_[EMOTESTATE::NUM];

    //ゲームが始まってからのフレーム数
    int gameFlame_;

    //アニメーションとかが始まってからのフレーム数
    int animationFlame_;

    //それぞれのアニメーションの終わりフレーム
    int idleEndFlame_;
    int moveEndFlame_;
    int applauseEndFlame_;
    int bowEndFlame_;

    //拍手が手を合わせるタイミングのフレーム
    int changeApplauseTiming_;

    //ずっと拍手させるためのフラグ
    bool changeApplauseFlag_;

    float totalMouseMoveX_;
    float totalMouseMoveY_;

private:

    //stateを変更
    void ChangePlayerState(PLAYERSTATE nextState);

    //State毎の初期化と解放処理
    void OnEnterPlayerState(PLAYERSTATE state);
    void OnLeavePlayerState(PLAYERSTATE state);

    //animationstateを変更
    void ChangeEmoteState(EMOTESTATE nextState);

    //animationState毎の初期化と解放処理
    void OnEnterEmoteState(EMOTESTATE state);
    void OnLeaveEmoteState(EMOTESTATE state);


    void Idle_Update();
    void Move_Update();
    void Action_Update();
    void Emote_Update();
    void Emote_Draw();

    //対応するキーが押されたらそのstateにする
    void CheckMoveKey();
    void CheckEmoteKey();
    
    //エモート中から待機状態へ
    void ChangeToIdle();

    void Move_Player();
    void Move_Camera();
};