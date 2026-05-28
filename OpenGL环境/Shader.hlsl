// ==========================================================
// 1. 结构体定义 (输入与输出)
// ==========================================================

// CPU 传给 GPU 的数据结构
struct VS_INPUT
{
    float4 pos : POSITION; // 顶点位置 (x, y, z, w)
    float4 color : COLOR; // 顶点颜色 (r, g, b, a)
};

// 顶点着色器处理后，传给像素着色器的数据结构
struct PS_INPUT
{
    float4 pos : SV_POSITION; // 裁剪空间下的位置 (System Value Position)
    float4 color : COLOR; // 颜色
};

// ==========================================================
// 2. 顶点着色器 (Vertex Shader)
// 功能：处理顶点位置，把 3D 坐标转换到屏幕上
// ==========================================================

PS_INPUT VSMain(VS_INPUT input)
{
    PS_INPUT output = (PS_INPUT) 0;

    // 直接把输入的位置赋给输出
    // 注意：这里我们假设输入的坐标已经是“裁剪空间”坐标 (-1 到 1)
    output.pos = input.pos;

    // 把颜色传递下去
    output.color = input.color;

    return output;
}

// ==========================================================
// 3. 像素着色器 (Pixel Shader)
// 功能：计算每一个像素的颜色
// ==========================================================

float4 PSMain(PS_INPUT input) : SV_Target
{
    // 返回颜色
    // 这里直接返回插值后的颜色
    return input.color;
}