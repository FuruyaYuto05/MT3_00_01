#include <Novice.h>

#define _USE_MATH_DEFINES
#include <math.h>

#include <assert.h>

const char kWindowTitle[] = "LE2D_20_フルヤユウト";

struct Vector3 {
    float x;
    float y;
    float z;
};

// --- Vector関数群 ---
// 加算
Vector3 Add(const Vector3& v1, const Vector3& v2) {
    return { v1.x + v2.x, v1.y + v2.y, v1.z + v2.z };
}

// 減算
Vector3 Subtract(const Vector3& v1, const Vector3& v2) {
    return { v1.x - v2.x, v1.y - v2.y, v1.z - v2.z };
}

// スカラー倍
Vector3 Multiply(float scalar, const Vector3& v) {
    return { v.x * scalar, v.y * scalar, v.z * scalar };
}

// 内積
float Dot(const Vector3& v1, const Vector3& v2) {
    return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
}

// 長さ
float Length(const Vector3& v) {
    return sqrtf(v.x * v.x + v.y * v.y + v.z * v.z);
}

// 正規化
Vector3 Normalize(const Vector3& v) {
    float length = Length(v);
    if (length == 0.0f) return { 0, 0, 0 };  // 0除算対策
    return { v.x / length, v.y / length, v.z / length };
}

// --- 描画用関数 ---
static const int kColumnWidth = 60;
static const int kRowHeight = 20;

void VectorScreenPrintf(int x, int y, const Vector3& vector, const char* label) {
    Novice::ScreenPrintf(x, y, "%.02f", vector.x);
    Novice::ScreenPrintf(x + kColumnWidth, y, "%.02f", vector.y);
    Novice::ScreenPrintf(x + kColumnWidth * 2, y, "%.02f", vector.z);
    Novice::ScreenPrintf(x + kColumnWidth * 3, y, "%s", label);
}

// WinMain
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {
    Novice::Initialize(kWindowTitle, 1280, 720);

    char keys[256] = { 0 };
    char preKeys[256] = { 0 };

    Vector3 v1{ 1.0f, 3.0f, -5.0f };
    Vector3 v2{ 4.0f, -1.0f, 2.0f };
    float k = 4.0f;

    while (Novice::ProcessMessage() == 0) {
        Novice::BeginFrame();

        memcpy(preKeys, keys, 256);
        Novice::GetHitKeyStateAll(keys);

        Vector3 resultAdd = Add(v1, v2);
        Vector3 resultSubtract = Subtract(v1, v2);
        Vector3 resultMultiply = Multiply(k, v1);
        float resultDot = Dot(v1, v2);
        float resultLength = Length(v1);
        Vector3 resultNormalize = Normalize(v2);

        VectorScreenPrintf(0, 0, resultAdd, " : Add");
        VectorScreenPrintf(0, kRowHeight, resultSubtract, " : Subtract");
        VectorScreenPrintf(0, kRowHeight * 2, resultMultiply, " : Multiply");
        Novice::ScreenPrintf(0, kRowHeight * 3, "%.02f : Dot", resultDot);
        Novice::ScreenPrintf(0, kRowHeight * 4, "%.02f : Length", resultLength);
        VectorScreenPrintf(0, kRowHeight * 5, resultNormalize, " : Normalize");

        Novice::EndFrame();

        if (preKeys[DIK_ESCAPE] == 0 && keys[DIK_ESCAPE] != 0) {
            break;
        }
    }

    Novice::Finalize();
    return 0;
}
