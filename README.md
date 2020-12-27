
# HPC-SamaraUniversity
Настоящий курс по дисциплине "Высокопроизводительные и облачные вычисления" предназначен для студентов магистерской программы ПМИ Самарского университета, осенний семестр 2020.

Лектор: [Якимов Павел Юрьевич](https://ssau.ru/staff/222993132-yakimov-pavel-yurevich) - доцент кафедры суперкомьютеров и общей информатики, к.т.н.

При подготовке курса были использованы следующие материалы:
- [NVIDIA CUDA C++ Programming Guide](https://docs.nvidia.com/cuda/cuda-c-programming-guide/index.html)
- [CUDA C++ Best Practices Guide](https://docs.nvidia.com/cuda/cuda-c-best-practices-guide/index.html)
- Материалы компании Applied Parallel Computing LLC
- Наработки автора

# Материалы для лекций

Здесь представлены слайды для презентаций, которые демонстрировались во время лекций:
- [1. Introduction to CUDA](/slides/1_Introduction.pdf)
- [2. CUDA Memory](/slides/2_Memory.pdf)
- [3. CUDA libraries](/slides/3_libraries.pdf)
- [4. Thrust library](/slides/4_thrust.pdf)
- [5. Multi-GPU](/slides/5_mpgu_compressed.pdf)
- [6. PyCUDA](/slides/6_pycuda-ru.pdf)
- [7. Profiling](/slides/7_Profiling.pdf)

# Видеоматериалы

Ссылки на видеозаписи лекций:
- [Лекция 1: Интро](https://bbb.ssau.ru/playback/presentation/2.0/playback.html?meetingId=b76cc06c5f576c9314c26c033cc5df63fbd1269f-1599470203236)
- [Лекция 2: CUDA basics](https://bbb.ssau.ru/playback/presentation/2.0/playback.html?meetingId=b76cc06c5f576c9314c26c033cc5df63fbd1269f-1600679665041)
- [Лекция 3: CUDA basics - продолжение + Виды памяти CUDA](https://bbb.ssau.ru/playback/presentation/2.0/playback.html?meetingId=b76cc06c5f576c9314c26c033cc5df63fbd1269f-1601450369352)
- [Лекция 4: Виды памяти CUDA - продолжение  + Библиотеки в CUDA](https://bbb.ssau.ru/playback/presentation/2.0/playback.html?meetingId=b76cc06c5f576c9314c26c033cc5df63fbd1269f-1601888085737)
- [Лекция 5: Библиотеки CUDA - продолжение](https://bbb.ssau.ru/playback/presentation/2.0/playback.html?meetingId=b76cc06c5f576c9314c26c033cc5df63fbd1269f-1602659393598)
- [Лекция 6: Библиотека Thrust](https://bbb.ssau.ru/playback/presentation/2.0/playback.html?meetingId=b76cc06c5f576c9314c26c033cc5df63fbd1269f-1603099247960)
- [Лекция 7: Multi-GPU](https://bbb.ssau.ru/playback/presentation/2.0/playback.html?meetingId=b76cc06c5f576c9314c26c033cc5df63fbd1269f-1603870100688)
- [Лекция 8: Продолжение Multi-GPU + разбор характеристик современных GPU](https://bbb.ssau.ru/playback/presentation/2.0/playback.html?meetingId=b76cc06c5f576c9314c26c033cc5df63fbd1269f-1605078230375)
- [Лекция 9: Python + CUDA](https://bbb.ssau.ru/playback/presentation/2.0/playback.html?meetingId=b76cc06c5f576c9314c26c033cc5df63fbd1269f-1606302273155)
- [Лекция 10: Профайлинг и оптимизация](https://bbb.ssau.ru/playback/presentation/2.0/playback.html?meetingId=b76cc06c5f576c9314c26c033cc5df63fbd1269f-1607498550649)


# Лабораторные работы

[Ссылка в Google Drive на таблицу с результатами по лабораторным работам](https://docs.google.com/spreadsheets/d/1BotpkxUXMNoUfIsEyczvU3dGOJ990JHVFX8byUVs-y4/edit?usp=sharing)

# Сценарий проведения зачета

Зачет будет проходить 28.12.2020 в 10:00 с использоанием bbb.sssau.ru и Zoom.

Вначале вам необходимо подключиться в BBB: https://bbb.ssau.ru/b/6av-zfc-qee. Там будет вся оперативная информация, там же появится ссылка на тест.

Зачет состоит из двух частей.

### Прохождение теста

Ссылка на тест будет предоставлена в самом начале зачета. Прохождение теста должно занять у вас не более 60 минут. Тест состоит из вопросов по материалам лекций + задачи в виде: “вот код, какой ответ?”. 
Настоятельно прошу максимально не пользоваться ничем, кроме того, что уже знаете.

Как только заканчиваете тест, пишите об этом в чате bbb.

### Собеседование

Собеседование будет проходить по новой ссылке с каждым по отдельности. Очередность собеседуемых будет определяться в основном треде зачета или в соответствии с тем, как будут приходить результаты теста.

В целом необходим только микрофон. Но легче общаться всё-таки с включенной камерой.

Во врмея собеседования сначала разберем ответы на вопросы теста.
Потом посмотрим на лабораторные работы и обсудим некоторые моменты в коде. Без лабораторных работ оценка за зачет выставлена не будет!
