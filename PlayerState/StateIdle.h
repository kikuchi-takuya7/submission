#pragma once
#include "../Engine/GameObject.h"

//◆◆◆を管理するクラス
class StateIdle : public GameObject
{

public:
    //コンストラクタ
    StateIdle(GameObject* parent);

    //デストラクタ
    ~StateIdle();

    //初期化
    void Initialize() override;

    //更新
    void Update() override;

    //描画
    void Draw() override;

    //開放
    void Release() override;
};