#ifndef MATRIXLOADER_ARMADILLO_BUILDER_H
#define MATRIXLOADER_ARMADILLO_BUILDER_H

/**
 * \file
 * \brief builders for Armadillo
 */


#include <matrixloader_builder.h>
#include <matrixloader_ext/utils/dense.h>
#include <armadillo>
/**
 * Implementation for armadillo sparse matrices
 */
template <class Value>
class ArmadilloSparseMatrixBuilder: public MatrixBuilder<arma::SpMat<Value>, Value>
{
	private:
		std::vector<unsigned long long int> sources;
		std::vector<unsigned long long int> dests;
		std::vector<Value> values;
	public:
		ArmadilloSparseMatrixBuilder() = default;

		void reserve(size_t, size_t, size_t nonzeros) override
		{
			sources.reserve(nonzeros);
			dests.reserve(nonzeros);
			values.reserve(nonzeros);
		}

		void set_entry(size_t source, size_t dest, Value const& value) override
		{
			sources.emplace_back(source);
			dests.emplace_back(dest);
			values.emplace_back(value);
		}

		arma::SpMat<Value> build() const override
		{
			arma::umat ls(sources);
			arma::umat ld(dests);
			arma::umat locations(arma::join_rows(ls,ld).t());
			arma::Col<Value> weights(values);
			return arma::SpMat<Value>{locations, weights};
		}
};

/**
 * Implementation for armadillo sparse matrices
 */
template <class Value>
class ArmadilloDenseMatrixBuilder: public DenseMatrixBuilder<arma::Mat<Value>, Value>
{
	public:
    ArmadilloDenseMatrixBuilder(): DenseMatrixBuilder<arma::Mat<Value>, Value>(false) {}
		arma::Mat<Value> build() const override
		{
      return arma::Mat<Value>(this->value.get(), this->get_rows(), this->get_columns());
		}
};

#endif /* end of include guard: ARMADILLO_H */
