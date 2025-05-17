#include <gtkmm.h>
#include <string>

class Calculator : public Gtk::Window {
public:
    Calculator();
    virtual ~Calculator();

private:
    // Widgets da interface
    Gtk::Entry m_Display;
    Gtk::Grid m_Grid;
    Gtk::Button m_Buttons[10], m_Button_Plus, m_Button_Minus, m_Button_Times, m_Button_Divide, m_Button_Clear, m_Button_Equals;

    // Variáveis internas
    std::string m_Operand, m_Operator, m_FullExpression;
    double m_Result;

    // Funções para manipulação dos sinais
    void on_button_click(const std::string& button_text);
    void on_clear_button_click();
    void on_equals_button_click();
};

Calculator::Calculator()
    : m_Operand(""), m_Operator(""), m_Result(0), m_FullExpression("") {

    set_title("Calculadora PLP");
    set_default_size(300, 400);

    // Layout principal
    Gtk::Box* m_Box = Gtk::manage(new Gtk::Box(Gtk::ORIENTATION_VERTICAL, 5));
    add(*m_Box);

    // Display (parte superior)
    m_Display.set_editable(false);
    m_Display.set_alignment(Gtk::ALIGN_CENTER);
    m_Display.set_text("0"); //No display começar com 0
    m_Box->pack_start(m_Display, Gtk::PACK_SHRINK);  // Fixa o display no topo da janela

    // Grid para os botões (parte inferior)
    Gtk::Box* m_BottomBox = Gtk::manage(new Gtk::Box(Gtk::ORIENTATION_VERTICAL));
    m_BottomBox->set_homogeneous(true);  // força todos os botões a terem o mesmo tamanho
    m_Box->pack_end(*m_BottomBox, Gtk::PACK_EXPAND_WIDGET); // Os botões vão ocupar o restante da janela

    // Grid para botões
    m_Grid.set_row_spacing(5);
    m_Grid.set_column_spacing(5);
    m_BottomBox->pack_start(m_Grid, Gtk::PACK_EXPAND_WIDGET); // Grid vai preencher a área dos botões

    // Botões (de 0 a 9)
    for (int i = 0; i < 10; i++) {
        m_Buttons[i].set_label(std::to_string(i));
        m_Buttons[i].signal_clicked().connect([this, i]() { on_button_click(std::to_string(i)); });
    }

    m_Button_Plus.set_label(" + ");
    m_Button_Minus.set_label(" - ");
    m_Button_Times.set_label(" * ");
    m_Button_Divide.set_label(" / ");
    m_Button_Clear.set_label("Clear");
    m_Button_Equals.set_label(" = ");

    // Conectando os sinais dos botões
    m_Button_Plus.signal_clicked().connect([this]() { on_button_click("+"); });
    m_Button_Minus.signal_clicked().connect([this]() { on_button_click("-"); });
    m_Button_Times.signal_clicked().connect([this]() { on_button_click("*"); });
    m_Button_Divide.signal_clicked().connect([this]() { on_button_click("/"); });
    m_Button_Clear.signal_clicked().connect([this]() { on_clear_button_click(); });
    m_Button_Equals.signal_clicked().connect([this]() { on_equals_button_click(); });

    // Adicionando os botões à grade
    for (int i = 0; i < 9; i++) {
        m_Grid.attach(m_Buttons[i + 1], i % 3, i / 3, 1, 1);
    }
    m_Grid.attach(m_Buttons[0], 0, 3, 1, 1);
    m_Grid.attach(m_Button_Plus, 3, 0, 1, 1);
    m_Grid.attach(m_Button_Minus, 3, 1, 1, 1);
    m_Grid.attach(m_Button_Times, 3, 2, 1, 1);
    m_Grid.attach(m_Button_Divide, 3, 3, 1, 1);
    m_Grid.attach(m_Button_Clear, 2, 3, 1, 1);
    m_Grid.attach(m_Button_Equals, 1, 3, 1, 1);

    show_all_children();
}

Calculator::~Calculator() {}

void Calculator::on_button_click(const std::string& button_text) {
    // Se o botão for um número
    if (button_text == "0" || button_text == "1" || button_text == "2" || button_text == "3" || button_text == "4" ||
        button_text == "5" || button_text == "6" || button_text == "7" || button_text == "8" || button_text == "9") {
        m_Operand += button_text;  // Adiciona o número ao operando
        m_FullExpression += button_text;  // Mantém a expressão completa
        m_Display.set_text(m_FullExpression);  // Atualiza o display com a expressão completa
    }
    // Se o botão for um operador
    else if (button_text == "+" || button_text == "-" || button_text == "*" || button_text == "/") {
        if (!m_Operand.empty()) {
            m_Result = std::stod(m_Operand); // Armazena o operando atual
        }
        m_Operator = button_text;  // Armazena o operador
        m_FullExpression += " " + m_Operator + " ";  // Adiciona o operador à expressão
        m_Operand.clear();  // Limpa o operando para o próximo número
        m_Display.set_text(m_FullExpression);  // Exibe a expressão até agora
    }
}

void Calculator::on_clear_button_click() {
    m_Operand.clear();
    m_Operator.clear();
    m_Result = 0;
    m_FullExpression.clear();
    m_Display.set_text("0");
}

void Calculator::on_equals_button_click() {
    if (!m_Operand.empty() && !m_Operator.empty()) {
        double second_operand = std::stod(m_Operand);

        // Realiza a operação de acordo com o operador
        if (m_Operator == "+") m_Result += second_operand;
        else if (m_Operator == "-") m_Result -= second_operand;
        else if (m_Operator == "*") m_Result *= second_operand;
        else if (m_Operator == "/") {
            if (second_operand != 0) m_Result /= second_operand;
            else {
                m_Display.set_text("Error");
                return;
            }
        }

        // Exibe o resultado final
        m_Display.set_text(std::to_string(m_Result));
        m_FullExpression += " = " + std::to_string(m_Result);  // Adiciona o resultado à expressão
        m_Operand = std::to_string(m_Result);  // Atualiza o operando com o resultado
        m_Operator.clear();
    }
}

int main(int argc, char *argv[]) {
    auto app = Gtk::Application::create(argc, argv, "org.gtkmm.calculadora");
    Calculator calc;
    return app->run(calc);
}