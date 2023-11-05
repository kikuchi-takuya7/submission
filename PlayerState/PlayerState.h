#pragma once
#include "../Engine/GameObject.h"
#include "StateAction.h"
#include "StateMove.h"
#include "StateAnimation.h"
#include "StateIdle.h"

//◆◆◆を管理するクラス
class PlayerState : public GameObject
{

public:
    //コンストラクタ
    PlayerState(GameObject* parent);

    //デストラクタ
    ~PlayerState();

    //初期化
    void Initialize() override;

    //更新
    void Update() override;

    //描画
    void Draw() override;

    //開放
    void Release() override;

private:
    
    
};