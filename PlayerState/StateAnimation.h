#pragma once
#include "../Engine/GameObject.h"

//◆◆◆を管理するクラス
class StateAnimation : public GameObject
{

public:
    //コンストラクタ
    StateAnimation(GameObject* parent);

    //デストラクタ
    ~StateAnimation();

    //初期化
    void Initialize() override;

    //更新
    void Update() override;

    //描画
    void Draw() override;

    //開放
    void Release() override;
};