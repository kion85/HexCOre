#include "Core.h"

Core::Core() {
    // Инициализация, если нужно
}

QString Core::processData(const QString &input) {
    // Обработка данных
    return QString("Обработано: %1").arg(input);
}
