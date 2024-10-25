#define WIN32_LEAN_AND_MEAN // Reduz o tamanho da biblioteca Windows, excluindo APIs menos usadas para tornar a compila��o mais eficiente
#include <windows.h>        // Inclui a biblioteca principal da API do Windows

// Definindo _In_ e _In_opt_ como vazios para evitar erro de compila��o no MinGW
#define _In_
#define _In_opt_

// Declara��o do prot�tipo da fun��o de tratamento de mensagens (callback) da janela
LRESULT CALLBACK WinProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

// Fun��o principal de aplicativos Windows
int APIENTRY WinMain(_In_ HINSTANCE hInstance,     // Identificador da inst�ncia do aplicativo atual
    _In_opt_ HINSTANCE hPrevInstance, // Identificador da inst�ncia anterior (geralmente NULL)
    _In_ LPSTR lpCmdLine,         // Linha de comando usada para iniciar o aplicativo
    _In_ int nCmdShow)            // Modo de exibi��o inicial da janela (minimizada, maximizada, etc.)
{
    HWND hwnd;           // Identificador para a janela criada
    MSG msg;             // Estrutura para armazenar mensagens de eventos
    WNDCLASS wndclass;   // Estrutura para definir a classe da janela (apar�ncia e comportamento)

    // Definindo as propriedades da janela
    wndclass.style = CS_HREDRAW | CS_VREDRAW;  // Redesenha a janela quando o tamanho horizontal ou vertical � alterado
    wndclass.lpfnWndProc = WinProc;            // Ponteiro para a fun��o de tratamento de mensagens (WinProc)
    wndclass.cbClsExtra = 0;                   // N�mero de bytes extras ap�s a estrutura da classe da janela (n�o usado)
    wndclass.cbWndExtra = 0;                   // N�mero de bytes extras ap�s a estrutura da janela (n�o usado)
    wndclass.hInstance = hInstance;            // Inst�ncia do aplicativo atual
    wndclass.hIcon = LoadIcon(NULL, IDI_APPLICATION); // �cone padr�o para a janela
    wndclass.hCursor = LoadCursor(NULL, IDC_ARROW);   // Cursor padr�o (seta)
    wndclass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH); // Cor de fundo branca
    wndclass.lpszMenuName = NULL;              // Sem menu para a janela
    wndclass.lpszClassName = "AppWindow";      // Nome da classe da janela

    // Registrando a classe da janela
    if (!RegisterClass(&wndclass))  // Retorna 0 se falhar ao registrar a classe
    {
        MessageBox(NULL, "Erro na cria��o da janela!", "Aplica��o", MB_ICONERROR); // Exibe mensagem de erro
        return 1; // Termina o programa com erro
    }

    // Criando a janela
    hwnd = CreateWindow(
        "AppWindow",                // Nome da classe da janela
        "Minha Aplica��o",          // T�tulo da janela
        WS_OVERLAPPEDWINDOW | WS_VISIBLE, // Estilo da janela com bordas e bot�es padr�o
        CW_USEDEFAULT,              // Posi��o X padr�o
        CW_USEDEFAULT,              // Posi��o Y padr�o
        CW_USEDEFAULT,              // Largura padr�o
        CW_USEDEFAULT,              // Altura padr�o
        NULL,                       // Sem janela m�e (janela principal)
        NULL,                       // Sem menu para a janela
        hInstance,                  // Inst�ncia do aplicativo
        NULL                        // Sem par�metros adicionais
    );

    // Verificando se a janela foi criada com sucesso
    if (!hwnd)  // Se a cria��o da janela falhar
    {
        MessageBox(NULL, "Falha ao criar a janela!", "Erro", MB_ICONERROR); // Exibe mensagem de erro
        return 1; // Termina o programa com erro
    }

    // Exibe a janela e atualiza seu conte�do
    ShowWindow(hwnd, nCmdShow); // Define o modo de exibi��o da janela
    UpdateWindow(hwnd);         // Solicita a atualiza��o da janela (for�a seu redesenho)

    // Loop de mensagens para o aplicativo Windows (gerencia eventos)
    while (GetMessage(&msg, NULL, 0, 0))  // L� a pr�xima mensagem da fila
    {
        TranslateMessage(&msg);   // Traduz mensagens (por exemplo, combina teclas)
        DispatchMessage(&msg);    // Envia a mensagem para a fun��o de tratamento de janela
    }

    return (int)msg.wParam;  // Retorna o c�digo de sa�da do programa
}

// Fun��o de processamento de mensagens para a janela
LRESULT CALLBACK WinProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    switch (msg)
    {
    case WM_DESTROY:           // Mensagem de encerramento da janela
        PostQuitMessage(0);    // Envia uma mensagem para terminar o loop de mensagens
        break;
    }

    // Processa qualquer outra mensagem usando a fun��o padr�o
    return DefWindowProc(hwnd, msg, wParam, lParam);
}
