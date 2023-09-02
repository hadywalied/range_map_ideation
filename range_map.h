#include <map>

template<typename K, typename V>
class range_map {
    V valBegin;
public:
    std::map<K, V> inner_map;

    // constructor associates whole range of K with val
    range_map(V const &val)
            : valBegin(val) {}

    // Assign value value to interval [begin, end).
    // Overwrite previous values in this interval.
    // Conforming to the C++ Standard Library conventions, the interval
    // includes begin, but excludes end.
    // If !( begin < end ), this designates an empty interval,
    // and assign must do nothing.
    void assign(K const &begin, K const &end, V const &value) {
        // INSERT YOUR SOLUTION HERE
        if (begin >= end) return;

        auto lowerBound = inner_map.lower_bound(begin);
        if (lowerBound == inner_map.end()) {
            //insertion at the end
            if (!(*lowerBound).first) {
                // insertion for the first time
                if (value == this->valBegin) return;
                inner_map.insert({begin, value});
            } else {
                // check that the last element in the range is not the key at hand
                auto last = std::prev(lowerBound);
                if ((*last).second == value) return;
                inner_map.insert({begin, value});
            }
        } else {
            //insertion in the middle lowerBound(next) prev(before) (k,v)(current)
            auto prev = std::prev(lowerBound);
            /*
             * conditions:
             * 1- if prev.value != current.value and next.value != current.value -> insert current (no mods)
             * 2- if prev.value != current.value and next.value == current.value -> insert current ( check next.key != current.key -> remove next)
             * 3- if prev.value == current.value and next.value != current.value -> do nothing
             * 4- if prev.value == current.value and next.value == current.value -> not applicable (shouldn't happen)
             */
            if ((*prev).second != value && (*lowerBound).second != value)
                inner_map.insert({begin, value});
            else if ((*prev).second != value && (*lowerBound).second == value) {
                inner_map.erase((*lowerBound).first);
                inner_map.insert({begin, value});
            } else {
                return;
            }
        }
    }

    // look-up of the value associated with key
    V const &operator[](K const &key) const {
        auto it = inner_map.upper_bound(key);
        if (it == inner_map.begin()) {
            return valBegin;
        } else {
            return (--it)->second;
        }
    }
};