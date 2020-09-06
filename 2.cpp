#include <fstream>
#include <vector>
#include <cmath>

#include <stdio.h>
#include <gmpxx.h>




int main() {
    enum Consts {
        SUPPOSED_LINE_SIZE = 500000001,
        FIRST_CHECKPOINT = 0,
        SECOND_CHECKPOINT = 99,
        THIRD_CHECKPOINT = 999999,
        FOURTH_CHECKPOINT = 499999999
    };

    std::vector<std::pair<double, double>> ans;
    ans.reserve(SUPPOSED_LINE_SIZE);
    
    std::ifstream file("variance_calc.tsv");
    if (!file) {
        printf("Can't open file");
        return -1;
    }
    
    mpq_class line(1);
    mpq_class sum(0);
    mpq_class sumSquare(0);
    while (file) {
        double tmp;
        file >> tmp;
        mpq_class t(tmp);
        
        sum += t;
        sumSquare += t * t;
        mpq_class stdDev(0);
        mpq_class sma = sum / line;
        if (line != 1) {
            stdDev = (sumSquare - sum * sma) / (line - 1);
        }
        ans.push_back(std::make_pair(sma.get_d(), sqrt(stdDev.get_d())));
        ++line;
    }

    printf("%.4lf %.8lf\n", ans[FIRST_CHECKPOINT].first, ans[FIRST_CHECKPOINT].second);
    printf("%.4lf %.8lf\n", ans[SECOND_CHECKPOINT].first, ans[SECOND_CHECKPOINT].second);
    printf("%.4lf %.8lf\n", ans[THIRD_CHECKPOINT].first, ans[THIRD_CHECKPOINT].second);
    printf("%.4lf %.8lf\n", ans[FOURTH_CHECKPOINT].first, ans[FOURTH_CHECKPOINT].second);
    return 0;
}
