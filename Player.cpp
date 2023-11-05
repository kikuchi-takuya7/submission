#include "Player.h"
#include "Engine/Model.h"
#include "Engine/Camera.h"
#include "Engine/Input.h"
#include "Engine/Debug.h"

//コンストラクタ
Player::Player(GameObject* parent)
    :GameObject(parent, "Player"),hIdleModel_(-1),hMoveModel_(-1),hAnimeModel_{-1,-1}
{
}

//デストラクタ
Player::~Player()
{
}

//初期化
void Player::Initialize()
{

    gameFlame_ = 0;
    animationFlame_ = 0;
    idleEndFlame_ = 100;
    moveEndFlame_ = 100;
    applauseEndFlame_ = 100;
    bowEndFlame_ = 50;
    changeApplauseTiming_ = 20;
    changeApplauseFlag_ = true;
    totalMouseMoveX_ = 0;
    totalMouseMoveY_ = 0;

    //モデルデータのロード
    hIdleModel_ = Model::Load("PlayerFbx/taikianime.fbx");
    assert(hIdleModel_ >= 0);

    hMoveModel_ = Model::Load("PlayerFbx/runmotion.fbx");
    assert(hMoveModel_ >= 0);

    //アニメーションが追加されたらこことhのenumに名前を追加する
    std::string emoteModelName[] = {
        "hakusyu.fbx",
        "ojigi.fbx",
    };

    std::string fName_Base = "PlayerFbx/";

    //モデルデータのロード
    for (int i = 0; i < NUM; i++) {
        hAnimeModel_[i] = Model::Load(fName_Base + emoteModelName[i]);
        assert(hAnimeModel_[i] >= 0);
    }


    Model::SetAnimFrame(hIdleModel_, 0, idleEndFlame_, 1);
    Model::SetAnimFrame(hMoveModel_, 0, moveEndFlame_, 1);
    Model::SetAnimFrame(hAnimeModel_[APPLAUSE], 0, moveEndFlame_, 1);
    Model::SetAnimFrame(hAnimeModel_[BOW], 0, bowEndFlame_, 1);

    transform_.position_.z = -5;
    transform_.rotate_.y = 180;

    currentPlayerState_ = IDLE;
    nextPlayerState_ = IDLE;
    currentEmoteState_ = NUM;
    nextEmoteState_ = NUM;

    XMFLOAT3 camTar = transform_.position_;
    camTar.y += 1.0f;
    //camTar.z += 5.0f;
    Camera::SetTarget(camTar);

    XMFLOAT3 camPos = transform_.position_;
    camPos.y += 3.0f;
    camPos.z += -3.0f;
    Camera::SetPosition(camPos);

}

//更新
void Player::Update()
{

    gameFlame_++;
    animationFlame_++;

    if (currentPlayerState_ != nextPlayerState_) {
        ChangePlayerState(nextPlayerState_);
    }


    switch (currentPlayerState_)
    {
    case IDLE:
        Idle_Update();
        break;
    case MOVE:
        Move_Update();
        break;
    case ACTION:
        Action_Update();
        break;
    case EMOTE:
        Emote_Update();
        CheckMoveKey();
        break;
    default:
        break;
    }

    
    //Move_Camera();

}

//描画
void Player::Draw()
{
    switch (currentPlayerState_)
    {
    case IDLE:
        Model::SetTransform(hIdleModel_, transform_);
        Model::Draw(hIdleModel_);
        break;
    case MOVE:
        Model::SetTransform(hMoveModel_, transform_);
        Model::Draw(hMoveModel_);
        break;
    case ACTION:

        break;
    case EMOTE:
        Emote_Draw();
        break;
    default:
        break;
    }
    
}

//開放
void Player::Release()
{
}

void Player::ChangePlayerState(PLAYERSTATE nextState)
{

    //開放して変更して初期化
    OnLeavePlayerState(currentPlayerState_);

    currentPlayerState_ = nextState;
    
    OnEnterPlayerState(currentPlayerState_);
}

void Player::OnEnterPlayerState(PLAYERSTATE state)
{
    animationFlame_ = 0;
    Model::SetAnimFrame(hIdleModel_, 0, idleEndFlame_, 1);
}

void Player::OnLeavePlayerState(PLAYERSTATE state)
{
}

void Player::ChangeEmoteState(EMOTESTATE nextState)
{
    //開放して変更して初期化
    OnLeaveEmoteState(currentEmoteState_);

    currentEmoteState_ = nextState;

    OnEnterEmoteState(currentEmoteState_);
}

void Player::OnEnterEmoteState(EMOTESTATE state)
{
    animationFlame_ = 0;
    changeApplauseFlag_ = true;
    Model::SetAnimFrame(hAnimeModel_[APPLAUSE], 0, applauseEndFlame_, 1);
    Model::SetAnimFrame(hAnimeModel_[BOW], 0, bowEndFlame_, 1);
}

void Player::OnLeaveEmoteState(EMOTESTATE state)
{
}

void Player::Idle_Update()
{

    CheckMoveKey();

    CheckEmoteKey();

}

void Player::Move_Update()
{
    
    //移動ボタンが押されてなければ
    if (!Input::IsKey(DIK_A) && !Input::IsKey(DIK_D) && !Input::IsKey(DIK_W) && !Input::IsKey(DIK_S))
    {
        nextPlayerState_ = IDLE;

    }

    CheckEmoteKey();

    Move_Player();


}

void Player::Action_Update()
{
}

void Player::Emote_Update()
{

    CheckEmoteKey();

    if (currentEmoteState_ != nextEmoteState_) {
        ChangeEmoteState(nextEmoteState_);
    }

    switch (currentEmoteState_)
    {
    case APPLAUSE:
        if (animationFlame_ >= applauseEndFlame_ && changeApplauseFlag_ == true) {
            Model::SetAnimFrame(hAnimeModel_[APPLAUSE], changeApplauseTiming_, applauseEndFlame_, 1);
            changeApplauseFlag_ = false;
        }
        break;

    case BOW:
        if (animationFlame_ >= bowEndFlame_) {
            ChangeToIdle();
        }
        break;

    default:
        break;
    }
}

void Player::Emote_Draw()
{

    switch (currentEmoteState_)
    {
    case APPLAUSE:
        Model::SetTransform(hAnimeModel_[APPLAUSE], transform_);
        Model::Draw(hAnimeModel_[APPLAUSE]);
        break;
    case BOW:
        Model::SetTransform(hAnimeModel_[BOW], transform_);
        Model::Draw(hAnimeModel_[BOW]);
        break;
    default:
        break;
    }
}

void Player::CheckMoveKey()
{
    if (Input::IsKey(DIK_A) || Input::IsKey(DIK_D) || Input::IsKey(DIK_W) || Input::IsKey(DIK_S))
    {
        nextPlayerState_ = MOVE;
    }

}

void Player::CheckEmoteKey()
{
    if (Input::IsKeyDown(DIK_1))
    {
        nextPlayerState_ = EMOTE;
        nextEmoteState_ = APPLAUSE;
    }
    if (Input::IsKeyDown(DIK_2))
    {
        nextPlayerState_ = EMOTE;
        nextEmoteState_ = BOW;
    }

}

void Player::ChangeToIdle()
{
    nextPlayerState_ = IDLE;
    //nextとcurrent一緒に変えちゃうのよくない気がする
    nextEmoteState_ = NUM;
    currentEmoteState_ = NUM;
}

void Player::Move_Player()
{
    XMFLOAT3 fMove = XMFLOAT3(0, 0, 0);

    if (Input::IsKey(DIK_A))
    {
        fMove.x = -0.1f;
    }
    if (Input::IsKey(DIK_D))
    {
        fMove.x = 0.1f;
    }
    if (Input::IsKey(DIK_W))
    {
        fMove.z = 0.1f;
    }
    if (Input::IsKey(DIK_S))
    {
        fMove.z = -0.1f;
    }

    //斜め移動でも足が速くならないように。なってる気がする
    XMVECTOR vMove = XMLoadFloat3(&fMove);
    vMove = XMVector3Normalize(vMove);
    XMStoreFloat3(&fMove, vMove);
    fMove.x /= 10;
    fMove.z /= 10;

    transform_.position_.x += fMove.x;
    transform_.position_.z += fMove.z;


    //短いほうの角度だけ求める向き方向
    XMVECTOR vLength = XMVector3Length(vMove);
    float length = XMVectorGetX(vLength);

    if (length != 0) {
        XMVECTOR vFront = { 0,0,1,0 };
        //vMove = XMVector3Normalize(vMove);

        XMVECTOR vDot = XMVector3Dot(vFront, vMove);
        float dot = XMVectorGetX(vDot);
        float angle = acos(dot);

        XMVECTOR vCross = XMVector3Cross(vFront, vMove);
        if (XMVectorGetY(vCross) < 0) {

            angle *= -1;
        }


        transform_.rotate_.y = XMConvertToDegrees(angle);
    }
}

void Player::Move_Camera()
{


#if 0

    XMFLOAT3 mouseMove = Input::GetMouseMove();

    totalMouseMoveX_ += mouseMove.x;
    totalMouseMoveY_ += mouseMove.y;

    //度回転させる行列を作成
    XMMATRIX rotY = XMMatrixRotationY(XMConvertToRadians(totalMouseMoveY_));
    XMMATRIX rotX = XMMatrixRotationX(XMConvertToRadians(totalMouseMoveX_));

    //現在の位置をベクトル型に変換
    XMVECTOR pos = XMLoadFloat3(&transform_.position_);

    XMFLOAT3 camPos = Camera::GetPosition();

    XMVECTOR test = XMLoadFloat3(&camPos);

    //移動ベクトルを変形 (洗車と同じ向きに回転) させる
    test = XMVector3TransformCoord(test, rotY);

    Camera::SetPosition(test);

#else
    /////////////////////////////////////////////////////////////////
    // ⓵　現在のカメラの注視点と視点を使って、XZ平面上での、
    //      注視点から視点までのベクトル(toCameraPosXZ)と長さ(toCameraPosXZLen)を求める。
    /////////////////////////////////////////////////////////////////
    XMFLOAT3 camPos = Camera::GetPosition();
    XMFLOAT3 camTar = Camera::GetTarget();
    XMVECTOR toCameraPosXZ = camPos - camTar;

    float height = XMVectorGetY(toCameraPosXZ);     //視点へのY方向の高さは、後で使うのでバックアップしておく。
    toCameraPosXZ = XMVectorSetY(toCameraPosXZ, 0); //XZ平面にするので、Yは0にする。
    float toCameraPosXZLen = Length(toCameraPosXZ); //XZ平面上での視点と注視点の距離を求める。
    XMVECTOR toCamPosNormalize = XMVector3Normalize(toCameraPosXZ);          //単位ベクトル化。
    
    /////////////////////////////////////////////////////////////////
    // ⓶　新しい注視点をアクターの座標から決める。
    /////////////////////////////////////////////////////////////////
    XMVECTOR target = XMLoadFloat3(&transform_.position_);
    target += XMVectorSetY(target, 5.0f);
    target += XMVectorSetX(target, -5.0f);
    XMFLOAT3 floatTarget = transform_.position_;
    floatTarget.y += 2.0f;
    floatTarget.z += -5.0f;

    /////////////////////////////////////////////////////////////////
    // ⓷　新しい注視点と現在のカメラの視点を使って、XZ平面上での、
    //     注視点から視点までのベクトル(toNewCameraPos)を求める。
    /////////////////////////////////////////////////////////////////
    XMVECTOR toNewCameraPos = floatTarget - camPos; //新しい注視点からカメラの始点へ向かうベクトルを求める。////////////////////////////////////////
    toNewCameraPos = XMVectorSetY(toNewCameraPos, 0.0f);              //XZ平面にするので、Yは0にする。
    XMVECTOR toNewCamPosNormalize = XMVector3Normalize(toNewCameraPos);         //単位ベクトル化。

    /////////////////////////////////////////////////////////////////
    // ⓸　１と２と３で求めた情報を使って、新しい視点を決定する。
    /////////////////////////////////////////////////////////////////
    //ちょっとづつ追尾。
    float weight = 0.7f;  //このウェイトの値は0.0～1.0の値をとる。1.0に近づくほど追尾が強くなる。
    toNewCamPosNormalize = toNewCamPosNormalize * weight + toCameraPosXZ * (1.0f - weight);
    toNewCamPosNormalize = XMVector3Normalize(toNewCamPosNormalize);
    toNewCamPosNormalize *= toCameraPosXZLen;
    toNewCamPosNormalize = XMVectorSetY(toNewCamPosNormalize, height);              //高さを戻す。
    XMVECTOR newCamPos = target + toCamPosNormalize;  //これで新しい視点が決定。

    /////////////////////////////////////////////////////////////////
    // ⓹　視点と注視点をカメラに設定して終わり。
    /////////////////////////////////////////////////////////////////
    Camera::SetPosition(newCamPos);
    Camera::SetTarget(floatTarget);

#endif

}

