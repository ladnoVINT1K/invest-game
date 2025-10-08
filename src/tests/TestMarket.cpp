#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"
#include "../core/MarketModel.h"
#include <vector>
#include <algorithm>
#include <iostream>
#include <string>
#include <cmath>

int main() {
    MarketModel market;

    // Симулируем 100 дней
    for(int i=0; i<100; ++i)
        market.update();

    const auto& candles = market.getCandles("gold");
    if(candles.empty()) {
        std::cout << "Нет свечей!" << std::endl;
        return 1;
    }

    // Настройки изображения
    const int width = 1200;
    const int height = 600;
    const int margin = 60;
    std::vector<unsigned char> image(width * height * 3, 255); // белый фон

    // Определяем min/max цену
    double minPrice = candles.front().low;
    double maxPrice = candles.front().high;
    for(const auto& c : candles) {
        minPrice = std::min(minPrice, c.low);
        maxPrice = std::max(maxPrice, c.high);
    }

    auto priceToY = [&](double p){
        return margin + (int)((maxPrice - p)/(maxPrice - minPrice)*(height - 2*margin));
    };

    int candleWidth = std::max(1, (width - 2*margin) / (int)candles.size() / 2);

    // Рисуем горизонтальную сетку и подписи цены
    for(int i=0;i<=5;i++){
        int y = margin + i*(height - 2*margin)/5;
        for(int x=margin;x<width-margin;x++){
            for(int k=0;k<3;k++) image[3*(y*width+x)+k] = 200;
        }
        // подпись цены (примерно)
        int priceLabel = (int)(maxPrice - i*(maxPrice - minPrice)/5);
        std::string label = std::to_string(priceLabel);
        // простое рисование символов не делаем, просто для ориентира
        // можно интегрировать с графической библиотекой для настоящих надписей
    }

    // Рисуем свечи и скользящее среднее
    std::vector<double> ma;
    int maPeriod = 5;

    for(size_t i=0;i<candles.size();i++){
        const auto& c = candles[i];
        int x = margin + i*2*candleWidth;

        // Цвет свечи по росту/падению и волатильности
        double vol = 1.0; // placeholder, можно брать из state.volatility
        unsigned char color[3];
        if(c.close >= c.open){
            color[0] = 0;
            color[1] = std::min(255, (int)(255*vol));
            color[2] = 0;
        } else {
            color[0] = std::min(255, (int)(255*vol));
            color[1] = 0;
            color[2] = 0;
        }

        int yOpen = priceToY(c.open);
        int yClose = priceToY(c.close);
        int yHigh = priceToY(c.high);
        int yLow = priceToY(c.low);

        int yTop = std::min(yOpen,yClose);
        int yBottom = std::max(yOpen,yClose);

        // тело свечи
        for(int xi=x;xi<x+candleWidth;xi++)
            for(int yi=yTop;yi<=yBottom;yi++)
                if(xi<width && yi<height)
                    for(int k=0;k<3;k++) image[3*(yi*width+xi)+k] = color[k];

        // тень
        int xc = x+candleWidth/2;
        for(int yi=yHigh;yi<yTop;yi++)
            if(xc<width && yi<height)
                for(int k=0;k<3;k++) image[3*(yi*width+xc)+k] = color[k];
        for(int yi=yBottom+1;yi<=yLow;yi++)
            if(xc<width && yi<height)
                for(int k=0;k<3;k++) image[3*(yi*width+xc)+k] = color[k];

        // скользящее среднее
        ma.push_back(c.close);
        if(ma.size() >= maPeriod){
            double sum=0;
            for(int j=i-maPeriod+1;j<=i;j++) sum+=candles[j].close;
            double avg = sum/maPeriod;
            int yMA = priceToY(avg);

            if(i>0){
                int xPrev = margin + (i-1)*2*candleWidth + candleWidth/2;
                double prevSum = 0;
                for(int j=i-maPeriod;j<i;j++) prevSum+=candles[j].close;
                int yPrev = priceToY(prevSum/(double)maPeriod);

                // рисуем линию MA синим
                int dx = xc - xPrev;
                int dy = yMA - yPrev;
                int steps = std::max(abs(dx),abs(dy));
                for(int s=0;s<=steps;s++){
                    int px = xPrev + s*dx/steps;
                    int py = yPrev + s*dy/steps;
                    if(px<width && py<height)
                        image[3*(py*width+px)+0] = 0,
                        image[3*(py*width+px)+1] = 0,
                        image[3*(py*width+px)+2] = 255;
                }
            }
        }
    }

    std::string filename = "gold_candles_pro.png";
    if(stbi_write_png(filename.c_str(), width, height, 3, image.data(), width*3))
        std::cout << "PRO-график сохранён в " << filename << std::endl;
    else
        std::cout << "Ошибка при сохранении PRO-графика!" << std::endl;

    return 0;
}
