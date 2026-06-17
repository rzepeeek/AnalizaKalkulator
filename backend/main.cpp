#include "httplib.h"
#include <string>
#include <sstream>
#include <vector>
#include <cmath>
#include <regex>

using namespace httplib;

std::vector<std::string> split(
    const std::string& str,
    char delimiter)
{
    std::vector<std::string> tokens;
    std::stringstream ss(str);
    std::string token;

    while(std::getline(ss, token, delimiter))
        tokens.push_back(token);

    return tokens;
}

int main()
{
    Server svr;

    svr.Options("/integral",
    [](const Request&, Response& res)
    {
        res.set_header("Access-Control-Allow-Origin", "*");
        res.set_header("Access-Control-Allow-Methods", "POST, OPTIONS");
        res.set_header("Access-Control-Allow-Headers", "*");
    });

    svr.Post("/integral",
    [](const Request& req, Response& res)
    {
        res.set_header("Access-Control-Allow-Origin", "*");

        std::vector<std::string> data =
            split(req.body, '|');

        if(data.size() < 3)
        {
            res.set_content("Bledne dane", "text/plain");
            return;
        }

        std::string expr = data[0];
        std::string expr2 = data[1];
        std::string type = data[2];

        std::string wynik;

        if(type == "derivative")
{
    std::regex powerRegex("^x\\^(\\d+)$");
    std::smatch match;

    if(expr == "x")
    {
        wynik =
            "<h3>Pochodna</h3>"
            "$$\\frac{d}{dx}(x)=1$$";
    }

    else if(std::regex_match(expr, match, powerRegex))
    {
        int n = std::stoi(match[1]);

        wynik =
            "<h3>Pochodna</h3>"
            "$$\\frac{d}{dx}(x^{"
            + std::to_string(n)
            + "})="
            + std::to_string(n)
            + "x^{"
            + std::to_string(n-1)
            + "}$$";
    }

    else if(expr == "sin(x)")
    {
        wynik =
            "<h3>Pochodna</h3>"
            "$$\\frac{d}{dx}(sin(x))=cos(x)$$";
    }

    else if(expr == "cos(x)")
    {
        wynik =
            "<h3>Pochodna</h3>"
            "$$\\frac{d}{dx}(cos(x))=-sin(x)$$";
    }
    else if(expr == "e^x")
    {
        wynik =
            "<h3>Pochodna</h3>"
            "$$\\frac{d}{dx}(e^x)=e^x$$";
    }

    else if(expr == "ln(x)")
    {
        wynik =
            "<h3>Pochodna</h3>"
            "$$\\frac{d}{dx}(ln(x))=\\frac{1}{x}$$";
    }

    else
    {
        wynik =
            "<b>Nie znam jeszcze tej pochodnej.</b>";
    }
}
else if(type == "indefinite")
{
    std::regex powerRegex("^x\\^(\\d+)$");
    std::smatch match;

    if(expr == "x")
    {
        wynik =
            "<h3>Całka nieoznaczona</h3>"
            "$$\\int x\\,dx$$"
            "$$=\\frac{x^2}{2}+C$$";
    }
    else if(std::regex_match(expr, match, powerRegex))
    {
        int n = std::stoi(match[1]);

        wynik =
            "<h3>Całka nieoznaczona</h3>"
            "$$\\int x^{" + std::to_string(n) + "}\\,dx$$"
            "$$=\\frac{x^{" + std::to_string(n + 1) +
            "}}{" + std::to_string(n + 1) + "}+C$$";
    }
    else if(expr == "sin(x)")
    {
        wynik =
            "<h3>Całka nieoznaczona</h3>"
            "$$\\int sin(x)\\,dx$$"
            "$$=-cos(x)+C$$";
    }
    else if(expr == "cos(x)")
    {
        wynik =
            "<h3>Całka nieoznaczona</h3>"
            "$$\\int cos(x)\\,dx$$"
            "$$=sin(x)+C$$";
    }
    else if(expr == "e^x")
    {
        wynik =
            "<h3>Całka nieoznaczona</h3>"
            "$$\\int e^x dx$$"
            "$$=e^x+C$$";
    }

    else if(expr == "ln(x)")
    {
        wynik =
            "<h3>Całka nieoznaczona</h3>"
            "$$\\int ln(x)dx$$"
            "$$=xln(x)-x+C$$";
    }
    else
    {
        wynik =
            "<b>Nie znam jeszcze tej całki.</b>";
    }
}
else if(type == "definite")
{
    if(data.size() < 4)
    {
        wynik = "Brak granic";
    }
    else
    {
        double a = std::stod(data[3]);
        double b = std::stod(data[4]);

        std::regex powerRegex("^x\\^(\\d+)$");
        std::smatch match;

        if(std::regex_match(expr, match, powerRegex))
        {
            int n = std::stoi(match[1]);

            double Fb =
                std::pow(b, n + 1) / (n + 1);

            double Fa =
                std::pow(a, n + 1) / (n + 1);

            double result =
                Fb - Fa;

            wynik =
                "<h3>Całka oznaczona</h3>"

                "$$F(x)=\\frac{x^{"
                + std::to_string(n + 1)
                + "}}{"
                + std::to_string(n + 1)
                + "}$$"

                "<br>"

                "$$F("
                + std::to_string((int)b)
                + ")="
                + std::to_string(Fb)
                + "$$"

                "<br>"

                "$$F("
                + std::to_string((int)a)
                + ")="
                + std::to_string(Fa)
                + "$$"

                "<br>"

                "$$"
                + std::to_string(Fb)
                + "-"
                + std::to_string(Fa)
                + "="
                + std::to_string(result)
                + "$$"

                "<br>"

                "$$\\approx "
                + std::to_string(result)
                + "$$";
        }

                else if(expr == "sin(x)")
        {
            double result =
                (-cos(b)) - (-cos(a));

            wynik =
                "<h3>Całka oznaczona</h3>"
                "$$\\int_{" + std::to_string((int)a) +
                "}^{" + std::to_string((int)b) +
                "}sin(x)dx$$"
                "$$\\approx " +
                std::to_string(result) +
                "$$";
        }
        else if(expr == "cos(x)")
        {
            double result =
                sin(b) - sin(a);

            wynik =
                "<h3>Całka oznaczona</h3>"
                "$$\\int_{"
                + std::to_string((int)a)
                + "}^{"
                + std::to_string((int)b)
                + "}cos(x)dx$$"

                "$$\\approx "
                + std::to_string(result)
                + "$$";
        }

        else if(expr == "ln(x)")
        {
            if(a <= 0 || b <= 0)
            {
                wynik =
                    "Dla ln(x) granice muszą być większe od 0";
            }
            else
            {
                double Fa =
                    a * log(a) - a;

                double Fb =
                    b * log(b) - b;

                double result =
                    Fb - Fa;

                wynik =
                    "<h3>Całka oznaczona</h3>"
                    "$$\\int_{"
                    + std::to_string((int)a)
                    + "}^{"
                    + std::to_string((int)b)
                    + "}ln(x)dx$$"
                    "$$\\approx "
                    + std::to_string(result)
                    + "$$";
            }
        }

        else
        {
            wynik =
                "Ta calka oznaczona nie jest jeszcze obslugiwana";
        }
    }
}

        else if(type == "area_between")
        {
            double a = std::stod(data[3]);
            double b = std::stod(data[4]);

            if(expr == "x^2" &&
            expr2 == "x")
            {
                double result =
                    (b*b/2.0 - a*a/2.0)
                    -
                    ((b*b*b)/3.0 -
                    (a*a*a)/3.0);

                wynik =
                    "<h3>Pole między krzywymi</h3>"
                    "$$P=\\int_a^b(f(x)-g(x))dx$$"
                    "$$\\approx "
                    + std::to_string(result)
                    + "$$";
            }
            else
            {
                wynik =
                    "Ta para funkcji nie jest jeszcze obsługiwana";
            }
        }

        else if(type == "volume")
        {
            double a = std::stod(data[3]);
            double b = std::stod(data[4]);

            if(expr == "x")
            {
                double result =
                    M_PI *
                    (
                        (b*b*b)/3.0 -
                        (a*a*a)/3.0
                    );

                wynik =
                    "<h3>Objętość bryły obrotowej</h3>"
                    "$$V=\\pi\\int_a^b(f(x))^2dx$$"
                    "$$\\approx "
                    + std::to_string(result)
                    + "$$";
            }
            else
            {
                wynik =
                    "Ta funkcja nie jest jeszcze obsługiwana";
            }
        }

        res.set_content(wynik, "text/plain");
    });

    svr.listen("localhost", 8080);
}