#include <optional>
#include <vector>

namespace dys {
    template<typename Energy, typename Storage = std::vector<Energy>>
    class accumulator {
    public:
        explicit accumulator(std::size_t, Energy = 0, Storage = {});

        std::optional<Energy> load(Energy);

        constexpr Energy level() const;

        constexpr std::size_t count() const;

    private:
        Energy level_;

        Storage rw_storage_;
        std::size_t rw_start_, rw_count_, rw_size_;
    };
    
    template<typename Energy, typename Storage>
    accumulator<Energy, Storage>::accumulator(std::size_t size, Energy init_level, Storage init_storage) {
        this->level_ = init_level;
        this->rw_storage_ = init_storage;
        this->rw_start_ = 0;
        this->rw_count_ = 0;
        this->rw_size_ = size;
    }

    template<typename Energy, typename Storage>
    std::optional<Energy> accumulator<Energy, Storage>::load(Energy charge_v) {
        std::optional<Energy> discharge;

        if (this->rw_count_ >= this->rw_size_) {
            auto discharge_v = this->rw_storage_[this->rw_start_];

            this->rw_storage_[this->rw_start_] = charge_v;
            this->rw_start_ = (this->rw_start_ + 1) % this->rw_size_;
            this->level_ = this->level_ - discharge_v + charge_v;

            discharge = {discharge_v};
        } else {
            this->rw_storage_[this->rw_start_ + this->rw_count_] = charge_v;
            this->rw_count_++;
            this->level_ += charge_v;

            discharge = std::nullopt;
        }

        return discharge;
    }
    
    template<typename Energy, typename Storage>
    constexpr Energy accumulator<Energy, Storage>::level() const {
        return this->level_;
    }

    template<typename Energy, typename Storage>
    constexpr std::size_t accumulator<Energy, Storage>::count() const {
        return this->rw_count_;
    }
}
