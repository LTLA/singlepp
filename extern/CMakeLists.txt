include(FetchContent)

FetchContent_Declare(
  knncolle 
  GIT_REPOSITORY https://github.com/LTLA/knncolle
  GIT_TAG c5a1776ebf10641d9bf8715e89cb2d965b06e899
)

FetchContent_MakeAvailable(knncolle)

FetchContent_Declare(
  tatami
  GIT_REPOSITORY https://github.com/LTLA/tatami
  GIT_TAG 69339622de87e406b6a6dca0c5ffd22daae42f67
)

FetchContent_MakeAvailable(tatami)

FetchContent_Declare(
  byteme
  GIT_REPOSITORY https://github.com/LTLA/byteme
  GIT_TAG f9ed015693c45424aa2835d79fc8e58128a24c93
)

FetchContent_MakeAvailable(byteme)
