include(FetchContent)

FetchContent_Declare(
        hard_assert
        GIT_REPOSITORY https://github.com/CesarBerriot/hard_assert.git
        GIT_TAG master
)
FetchContent_MakeAvailable(hard_assert)