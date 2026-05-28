#include <iostream>
#include <glad/glad.h>//引入OpenGL库
#include <GLFW/glfw3.h>

using namespace std;
/*实例化GLFW窗口_Window
（用 类_class 创建 对象_objec 的过程叫做 实例化_instantiation）
 帧缓冲，双缓冲_double buffer*/

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
//定义回调函数 
//告诉哪个窗口改变了；GLFW传给我最新的帧缓冲宽度（像素）；高度
{
	glViewport(0, 0, width, height);
	//glViewport函数可以将映射到标准化设备坐标(NDC)到窗口坐标(屏幕像素坐标)
}

void processInput(GLFWwindow* window) //创建 输入_input 函数
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
}

int main() 
{
	int width=0;
    int height=0;

	glfwInit();//用来 初始化_init GLFW
	//glfwWindowHint函数用于设置在创建窗口时的各种属性
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);//主版本号（Major）设为3
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);//次版本号（Minor）设为3，告诉GLFW使用OpenGL3.3
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	//建议_hint 库使用核心模式（Core-profile）

	GLFWwindow* window = glfwCreateWindow(800, 600, "LearnOpenGL", NULL, NULL);
//利用glfwCreateWindow函数 创建_create 窗口对象并返回GLFWwindow对象-LearnOpenGL
//函数参数包含窗口尺寸(>0);标题;NULL表示窗口模式，非则表示全屏;用于资源共享的窗口对象

if (window == NULL)//返回NULL表示Window创建失败
{
	std::cout << "Failed to create GLFW window" << std::endl;
	glfwTerminate();//调用gifwTerminalte函数释放glfw库占用的资源，防止内存泄露
	return -1;//安全退出；返回-1，让程序以异常状态退出，避免因为向下执行而报错
}

glfwMakeContextCurrent(window);//激活渲染环境，将指定window的上下文设为 当前_current 上下文_context

if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))//加载OpenGL函数指针前必须初始化glad
/*创建成功OpenGL上下文并设为当前后才可获取到地址
gladLoadGLLoader() 函数:GLAD库提供的总加载器;执行后会返回状态值
glfwGetProcAddress 根据函数名询问并返回某个OpenGL函数的内存地址
(GLADloadproc) 强制类型转换，将glfw函数转换为glad能够识别与使用的类型
if(!...) 如返回值失败，取反后为真，进入if语句块*/
{   
	cout << "Failed to initialize GLAD" << endl;
    return -1;//安全退出
}
 
glViewport(0, 0, 800, 600);//设置 视口_Viewprot 的 尺寸_Dimension (像素）
//window决定画布大小，viewprot决定作画大小
//1-2位参数控制window左下角位置，3-4位分别控制窗口宽度和高度

void framebuffer_size_callback(GLFWwindow * window, int width, int height);
//对window注册回调函数（Callback Function）让视口随窗口调整 缓冲_buffer

glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
//glfwSetFramebufferSizeCallback函数将窗口与回调函数绑定
//让glfw在改变帧缓冲时顺便调用被绑定的函数

while (!glfwWindowShouldClose(window)) //渲染循环(render loop)，让glfw退出前持续运行
//glfwWindowShouldClose函数检查glfw是否退出，如是，依靠while(!...取反后为假)返回true
{
	//输入
	processInput(window);//调用创建的输入函数来检测特定键是否被按下

	//渲染指令
	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);///清空屏幕颜色缓冲

	//检查并调用，交换缓冲
	glfwSwapBuffers(window);//交换颜色缓冲
	glfwPollEvents();//函数检查是否触发事件，更新状态
}

glfwTerminate();//调用函数释放内存
	return 0;
}




