/* Slice Usage Macros */

#define slice_of(_ptr) {                  \
    .ptr = _ptr,                          \
    .len = sizeof(_ptr) / sizeof(_ptr[0]) \
}

#define slice_from(_ptr, idx) {                    \
    .ptr = _ptr + idx,                             \
    .len = sizeof(_ptr) / ( idx + sizeof(_ptr[0])) \
}

#define slice_range(_ptr, start, end) { \
    .ptr = _ptr+start,                  \
    .len = end - start                  \
}

#define slice_get(slice, idx) slice.ptr[idx]
