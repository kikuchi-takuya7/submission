#pragma once
#include "Engine/GameObject.h"

//◆◆◆を管理するクラス
class TestFloor : public GameObject
{
    int hModel_;    //モデル番号
    //char objectID_; //どのオブジェクトかimguiが判別するためのオブジェクト
    bool isDelete_;

    bool isClose_;

public:
    //コンストラクタ
    TestFloor(GameObject* parent);

    //デストラクタ
    ~TestFloor();

    //初期化
    void Initialize() override;

    //更新
    void Update() override;

    //描画
    void Draw() override;

    //開放
    void Release() override;

    void Imgui_Window() override;

    void Imgui_Data_Edit() override;

    bool IsKillCheck();

    void DeleteMe();

    void DeleteStop();

};