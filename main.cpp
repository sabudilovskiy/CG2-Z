
#include <GL/glew.h>
#include <GLFW/glfw3.h>

// Вершинный шейдер
const char* vertexShaderSource = R"glsl(
    #version 330 core
    layout (location = 0) in vec2 aPos;
    layout (location = 1) in vec3 aNormal;

    out vec3 FragPos; // Передаем позицию фрагмента во фрагментный шейдер
    out vec3 Normal;

    void main() {
        gl_Position = vec4(aPos, 0.0, 1.0);
        FragPos = vec3(gl_Position.xy, 0.0);
        Normal = aNormal;
    }
)glsl";

// Фрагментный шейдер
// Фрагментный шейдер
const char* fragmentShaderSource = R"glsl(
    #version 330 core
    in vec3 FragPos; // Получаем позицию фрагмента из вершинного шейдера
    in vec3 Normal;
    out vec4 FragColor;

    uniform vec3 lightColor;
    uniform vec3 lightPos;
    uniform vec3 viewPos;

    void main() {
        // Расчет векторов направления света и взгляда
        vec3 norm = normalize(Normal);
        vec3 lightDir = normalize(lightPos - FragPos); // Используем FragPos для расчета направления света
        vec3 viewDir = normalize(viewPos - FragPos);

        // Диффузное освещение
        float diff = max(dot(norm, lightDir), 0.0);
        vec3 diffuse = diff * lightColor;

        // Рассчет коэффициента затухания тени
        float distance = length(lightPos - FragPos);
        float attenuation = 1.0 / (1.0 + 0.05 * distance + 1 * (distance * distance)); // Измененные коэффициенты затухания

        // Тень
        vec3 shadow = (1.0 - attenuation) * vec3(0.0); // Более явная тень

        // Освещенная часть
        vec3 light = diffuse * attenuation;

        // Результирующий цвет
        vec3 result = light * attenuation + shadow * (1 - attenuation);
        FragColor = vec4(result, 1.0);
    }
)glsl";






int main() {
    glfwInit();
    GLFWwindow* window = glfwCreateWindow(900, 900, "Red Square with Basic Lighting", nullptr, nullptr);
    glfwMakeContextCurrent(window);
    glewInit();

    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, nullptr);
    glCompileShader(vertexShader);

    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, nullptr);
    glCompileShader(fragmentShader);

    GLuint shaderProgram = glCreateProgram();

    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    glUseProgram(shaderProgram);
    int lightColorLoc = glGetUniformLocation(shaderProgram, "lightColor");
    int lightPosLoc = glGetUniformLocation(shaderProgram, "lightPos");
    int viewPosLoc = glGetUniformLocation(shaderProgram, "viewPos");

// Значения освещения
// Значения освещения
    glUniform3f(lightColorLoc, 1.0f, 1.0f, 1.0f); // белый цвет света
    glUniform3f(lightPosLoc, 0.0f, 0.0f, 0.5f);  // точечный свет сверху (примерно в центре экрана)
    glUniform3f(viewPosLoc, 0.0f, 0.0f, 1.0f);   // позиция камеры/наблюдателя

    float vertices[] = {
            // Позиции вершин  // Нормали
            -1.0f, -1.0f,     0.0f, 0.0f, 1.0f,
            1.0f, -1.0f,      0.0f, 0.0f, 1.0f,
            1.0f, 1.0f,       0.0f, 0.0f, 1.0f,
            -1.0f, 1.0f,      0.0f, 0.0f, 1.0f
    };

    unsigned int indices[] = {
            0, 1, 2,
            2, 3, 0
    };



    GLuint VBO, VAO, EBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(2 * sizeof(float)));
    glEnableVertexAttribArray(1);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    while (!glfwWindowShouldClose(window)) {
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glUseProgram(shaderProgram);
        glBindVertexArray(VAO);

        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
    glDeleteProgram(shaderProgram);

    glfwTerminate();
    return 0;
}
