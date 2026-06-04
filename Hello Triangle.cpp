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
	int width = 0;
	int height = 0;

	int success;
	char infoLog[512];

    unsigned int VBO;//声明一个非负整型变量用来存放VBOID
	unsigned int VAO;
    unsigned int vertexShader;//新建空顶点着色器
	unsigned int fragmentShader;//新建空片段着色器
	unsigned int shaderProgram;//创建着色器程序

	float vertices[] = {
      -0.5f,-0.5f,0.0f,
       0.5f,-0.5f,0.0f,
       0.0f,0.5f,0.0f
	};
	//以标准化设备坐标的形式定义一个数组
	//用来给OpenGL输入顶点data

	const char* vertexShaderSource = "#version 330 core\n"
		"layout (location = 0) in vec3 apos;\n"
		"void main()\n"
		"{\n"
		"   gl_Position = vec4(apos.x, apos.y,apos.z, 1.0);\n"
		"}\0";
	//顶点着色器源代码
	//硬编码GLSL源码时必须手动加换行符，且结尾加上空字符结束符

	const char* fragmentShaderSource = "#version 330 core\n"
		"out vec4 FragColor;\n"
		"void main()\n"
		"{\n"
		"FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
		"}\0";
	//片段着色器源代码

	glfwInit();//用来 初始化_init GLFW
	//glfwWindowHint函数用于设置在创建窗口时的各种属性
	//任何glfw函数使用前都要初始化！！！
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
		if(!...) 如返回值失败，取反后为真，进入if语句块
		*/
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

	//因为OpenGL是状态机，在执行管线前必须先初始化所有库以及创建window并绑定上下文！！！
	//顶点输入
	
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);//函数申请ID并存入对应地址的变量中
	glBindVertexArray(VAO);//绑定VAO
	glBindBuffer(GL_ARRAY_BUFFER, VBO);//将刚才的data绑定之下一步需要的位置
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	/*glBufferData函数将定义数据复制至绑定的buffer函数
	GL_ARRAY_BUFFER 指定缓冲区类型，将数据运至当前绑定的VBO
	sizeof(vertices) 指定搬运数据总大小 sizeof自动计算数组vertices占用空间
	vertices 指向需要搬运的原数据
	GL_STATIC_DRAW 性能提示 放置在显存内适合静态读取的区域 适合data不会或几乎不会改变
	GL_DYNAMIC_DRAW 适合data会有很多改变
	GL_STREAM_DRAW 适合data在每次绘制都会改变
	*/

	//编译顶点着色器
    vertexShader = glCreateShader(GL_VERTEX_SHADER);
	//该函数申请空间用于存放GLSL代码
	//参数 枚举常量 作用是告诉函数要创建“顶点着色器”
	//变量被该函数接受

	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	//参数1 告诉目标源码
	//参数2 源码字符串的数量
	//参数3 源码的指针
	//参数4 源码长度指示器 NULL为OpenGL自主计算（一般源码以\0结尾）
    glCompileShader(vertexShader);//将传入的源代码编译成GPU能使用的机器码

	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
		cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << endl;
	}//检测是否编译成功

	//编译片段着色器/类似编译顶点着色器过程
	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);//着色器类型变换
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	glCompileShader(fragmentShader);

	shaderProgram = glCreateProgram();//创建程序
	glAttachShader(shaderProgram, vertexShader);//链接着色器
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);

	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
		cout << "链接" << infoLog << endl;
	}//检测链接是否失败

	glUseProgram(shaderProgram);//激活程序对象

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);//删除着色器对象

	//链接顶点属性
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	//顶点缓冲数据 数据紧密排列 位置数据的位置在缓冲开头
	//参数1 指定需要配置的顶点属性
	//参数2 指定顶点属性的大小 由三个值组成
	//参数3 指定数据类型 float（GLSL中vec*都是由浮点数值组成）
	//参数4 是否希望数据被标准化(Normalize) 如果设置为TRUE，所有数据会被映射到0-1之间
	//参数5 步长(Stride) 连续组之间的间隔 （当数组紧密排列时，也可以设置为0来自动决定步长）
	//参数6 强制类型转换(void*)和参数(0) 表示位置数据在缓冲中起始位置的偏移量(Offset)
	glEnableVertexAttribArray(0);


	while (!glfwWindowShouldClose(window)) //渲染循环(render loop)，让glfw退出前持续运行
		//glfwWindowShouldClose函数检查glfw是否退出，如是，依靠while(!...取反后为假)返回true
	{
		//输入
		processInput(window);//调用创建的输入函数来检测特定键是否被按下

		//渲染指令
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);///清空屏幕颜色缓冲

	glUseProgram(shaderProgram);
	glBindVertexArray(VAO);
	glDrawArrays(GL_TRIANGLES, 0, 3);

		//检查并调用，交换缓冲
		glfwSwapBuffers(window);//交换颜色缓冲
		glfwPollEvents();//函数检查是否触发事件，更新状态
	}

	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteProgram(shaderProgram);//清理内存

	glfwTerminate();//调用函数释放内存
	return 0;
}

