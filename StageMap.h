#pragma once
#include "Engine/GameObject.h"

//◆◆◆を管理するクラス
class StageMap : public GameObject
{

public:
    //コンストラクタ
    StageMap(GameObject* parent);

    //デストラクタ
    ~StageMap();

    //初期化
    void Initialize() override;

    //更新
    void Update() override;

    //描画
    void Draw() override;

    //開放
    void Release() override;
};