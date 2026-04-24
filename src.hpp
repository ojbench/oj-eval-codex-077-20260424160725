// CrossArray implementation header for ACMOJ Problem 1410
// Implements a jagged 2D array of ints without using any libraries.

namespace sjtu {

class CrossArray{
private:
    int **lines_ptrs;      // pointers to each 1-D array (may be nullptr)
    int  *lines_sizes;     // sizes of each 1-D array (0 if nullptr)
    int    capacity;       // maximum number of parallel arrays
    int    inserted;       // count of inserted arrays (next insert index)

    static void copy_ints(int *dst, const int *src, int n) {
        for (int i = 0; i < n; ++i) dst[i] = src[i];
    }

public:
    explicit CrossArray(int lines)
        : lines_ptrs(nullptr), lines_sizes(nullptr), capacity(lines), inserted(0) {
        if (capacity < 0) capacity = 0;
        lines_ptrs = capacity ? new int*[capacity] : nullptr;
        lines_sizes = capacity ? new int[capacity] : nullptr;
        for (int i = 0; i < capacity; ++i) {
            lines_ptrs[i] = nullptr;
            lines_sizes[i] = 0;
        }
    }

    CrossArray(const CrossArray & o)
        : lines_ptrs(nullptr), lines_sizes(nullptr), capacity(o.capacity), inserted(o.inserted) {
        lines_ptrs = capacity ? new int*[capacity] : nullptr;
        lines_sizes = capacity ? new int[capacity] : nullptr;
        for (int i = 0; i < capacity; ++i) {
            lines_sizes[i] = o.lines_sizes ? o.lines_sizes[i] : 0;
            if (o.lines_ptrs && o.lines_ptrs[i] != nullptr) {
                int len = lines_sizes[i];
                if (len > 0) {
                    lines_ptrs[i] = new int[len];
                    copy_ints(lines_ptrs[i], o.lines_ptrs[i], len);
                } else {
                    lines_ptrs[i] = nullptr;
                }
            } else {
                lines_ptrs[i] = nullptr;
                lines_sizes[i] = 0;
            }
        }
    }

    CrossArray & WhichGreater(CrossArray & o) {
        long long a = 0, b = 0;
        for (int i = 0; i < capacity; ++i) a += (long long)lines_sizes[i];
        for (int i = 0; i < o.capacity; ++i) b += (long long)o.lines_sizes[i];
        if (a >= b) return *this;
        return o;
    }

    bool IsSame(const CrossArray & o) { return lines_ptrs == o.lines_ptrs; }

    bool InsertArrays(const int * Input, int size) {
        if (inserted >= capacity) return false;
        int *arr = nullptr;
        if (size > 0) {
            arr = new int[size];
            copy_ints(arr, Input, size);
        }
        lines_ptrs[inserted] = arr;
        lines_sizes[inserted] = size;
        ++inserted;
        return true;
    }

    void AppendArrays(const int * Input, int Line, int size) {
        int old_sz = lines_sizes[Line];
        int new_sz = old_sz + size;
        int *old_ptr = lines_ptrs[Line];
        if (size == 0) return; // no-op
        int *new_ptr = new int[new_sz];
        for (int i = 0; i < old_sz; ++i) new_ptr[i] = old_ptr[i];
        for (int i = 0; i < size; ++i) new_ptr[old_sz + i] = Input[i];
        if (old_ptr) delete [] old_ptr;
        lines_ptrs[Line] = new_ptr;
        lines_sizes[Line] = new_sz;
    }

    void DoubleCrossLength() {
        int new_cap = capacity * 2;
        int **new_ptrs = new int*[new_cap];
        int  *new_sizes = new int[new_cap];
        for (int i = 0; i < new_cap; ++i) {
            if (i < capacity) {
                new_ptrs[i] = lines_ptrs[i];
                new_sizes[i] = lines_sizes[i];
            } else {
                new_ptrs[i] = nullptr;
                new_sizes[i] = 0;
            }
        }
        if (lines_ptrs) delete [] lines_ptrs;
        if (lines_sizes) delete [] lines_sizes;
        lines_ptrs = new_ptrs;
        lines_sizes = new_sizes;
        capacity = new_cap;
    }

    const int * AtArray(int i) { return lines_ptrs[i]; }

    int & At(int i , int j) { return lines_ptrs[i][j]; }

    ~CrossArray() {
        if (lines_ptrs) {
            for (int i = 0; i < capacity; ++i) if (lines_ptrs[i]) delete [] lines_ptrs[i];
            delete [] lines_ptrs;
            lines_ptrs = nullptr;
        }
        if (lines_sizes) { delete [] lines_sizes; lines_sizes = nullptr; }
        capacity = 0; inserted = 0;
    }
};

} // namespace sjtu

