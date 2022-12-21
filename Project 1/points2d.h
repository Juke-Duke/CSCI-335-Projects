// Youssef Elshabasy
// Class for a representation of a sequence of 2D points.

#ifndef CSCI335_HOMEWORK1_POINTS2D_H_
#define CSCI335_HOMEWORK1_POINTS2D_H_

#include <array>
#include <iostream>
#include <cstddef>
#include <string>

namespace teaching_project
{
    /// @brief A representation for a sequence of 2D points.
    /// @tparam TNumber Number data type.
    template <typename TNumber> class Points2D
    {
    private:
        /// @brief Size of the sequence.
        size_t size_ = 0;

        /// @brief Sequence of 2D points.
        std::array<TNumber, 2>* sequence_ = nullptr;

    public:
        /// @brief Initializes a new instance of the Points2D class that is empty and has the default initial size of 0.
        Points2D() noexcept
            : size_(0), sequence_(nullptr) {}

        /// @brief Initializes a new instance of the Points2D class that contains elements deep copied from another Points2D class instance.
        /// @param rhs The Points2D class instance to deep copy from.
        Points2D(const Points2D& rhs) noexcept
            : size_(rhs.size_), sequence_(new std::array<TNumber, 2>[rhs.size_])
        {
            for (size_t i = 0; i < size_; ++i)
                sequence_[i] = rhs.sequence_[i];
        }

        /// @brief Initializes a new instance of the Points2D class that contains elements from an rvalue reference.
        /// @param rhs The rvalue reference to move from.
        Points2D(Points2D&& rhs) noexcept
            : size_(rhs.size_), sequence_(rhs.sequence_)
        {
            rhs.size_ = 0;
            rhs.sequence_ = nullptr;
        }

        /// @brief Initializes a new instance of the Points2D class that contains one point from a single std::array of two elements.
        /// @param point The std::array of 2D points to copy from.
        Points2D(const std::array<TNumber, 2>& point) noexcept
            : size_(1), sequence_(new std::array<TNumber, 2>[1])
        { sequence_[0] = point; }

        /// @brief Copy assignment operator overload.
        /// @param rhs The Points2D class instance to deep copy from.
        /// @return Sets the current instance to a deep copy of another Points2D class instance.
        Points2D& operator=(const Points2D& rhs) noexcept
        {
            Points2D copy = rhs;
            std::swap(*this, copy);
            return *this;
        }

        /// @brief Move assignment operator overload.
        /// @param rhs The rvalue reference to move to.
        /// @return Sets the current instance to an rvalue reference.
        Points2D& operator=(Points2D&& rhs) noexcept
        {
            if (this != &rhs)
            {
                delete[] sequence_;

                size_ = rhs.size_;
                sequence_ = rhs.sequence_;

                rhs.size_ = 0;
                rhs.sequence_ = nullptr;
            }

            return *this;
        }

        /// @brief Gets the number of points in the sequence.
        /// @return The size of the sequence.
        size_t size() const noexcept { return size_; }

        /// @brief Gets the 2D point at the specified index, can not be used for modification.
        /// @param location The index of the 2D point to get.
        /// @return The 2D point at the specified index.
        const std::array<TNumber, 2>& operator[](size_t location) const
        {
            if (location >= size_ || location < 0)
            {
                std::cerr << "ERROR: Index out of range." << std::endl;
                abort();
            }

            return sequence_[location];
        }

        /// @brief Adds the elements of another Points2D class instance to the current instance.
        /// @param points1 The first Points2D class instance to union from.
        /// @param points2 The second Points2D class instance to union from.
        /// @return A new instance of the Points2D class that contains elements union from two Points2D class instances.
        friend Points2D operator+(const Points2D& points1, const Points2D& points2) noexcept
        {
            Points2D sum;
            sum.size_ = std::max(points1.size_, points2.size_);
            sum.sequence_ = new std::array<TNumber, 2>[sum.size_];

            for (size_t i = 0; i < sum.size_; ++i)
            {
                sum.sequence_[i][0] = (i < points1.size_ ? points1[i][0] : 0) + (i < points2.size_ ? points2[i][0] : 0);
                sum.sequence_[i][1] = (i < points1.size_ ? points1[i][1] : 0) + (i < points2.size_ ? points2[i][1] : 0);
            }

            return sum;
        }

        /// @brief Displays a given sequence of 2D points to the console.
        /// @param out The output stream to display the sequence of 2D points to.
        /// @param points The Points2D class instance to display.
        /// @return The output stream to display the sequence of 2D points to.
        friend std::ostream& operator<<(std::ostream& out, const Points2D& points) noexcept
        {
            if (points.size_ == 0)
                return out << "()" << std::endl;

            for (size_t i = 0; i < points.size_; ++i)
                out << "(" << points[i][0] << ", " << points[i][1] << ") ";

            return out << std::endl;
        }

        /// @brief Reads a given sequence of 2D points from the console.
        /// @param in The input stream to read the sequence of 2D points from.
        /// @param points The Points2D class instance to read.
        /// @return The input stream to read the sequence of 2D points from.
        friend std::istream& operator>>(std::istream& in, Points2D& points)
        {
            delete[] points.sequence_;

            size_t size;
            in >> size;

            points.size_ = size;
            points.sequence_ = new std::array<TNumber, 2>[size];

            for (size_t i = 0; i < size * 2; i += 2)
            {
                std::array<TNumber, 2> point;
                TNumber x, y;

                if (in >> x && in >> y)
                {
                    point[0] = x;
                    point[1] = y;
                }
                else
                {
                    std::cerr << "ERROR" << std::endl;
                    abort();
                }

                points.sequence_[i / 2] = point;
            }

            std::cout << std::endl;

            return in;
        }

        /// @brief Deallocates the memory used by the sequence of 2D points.
        ~Points2D() noexcept
        {
            size_ = 0;
            delete[] sequence_;
            sequence_ = nullptr;
        }
    };
}

#endif