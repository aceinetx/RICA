#define CALLBACK_0(func, self) std::bind(&func, self)
#define CALLBACK_1(func, self) std::bind(&func, self, std::placeholders::_1)
#define CALLBACK_2(func, self)                                                 \
  std::bind(&func, self, std::placeholders::_1, std::placeholders::_2)
#define CALLBACK_3(func, self)                                                 \
  std::bind(&func, self, std::placeholders::_1, std::placeholders::_2, ,       \
            std::placeholders::_3)
