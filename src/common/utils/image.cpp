#include "image.hpp"

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>
#include <gsl/gsl>

namespace utils
{
	image::image(const std::string& image_data)
	{
		int channels{};
		auto* rgb_image = stbi_load_from_memory(reinterpret_cast<const uint8_t*>(image_data.data()), static_cast<int>(image_data.size()), &this->width, &this->height, &channels, STBI_rgb_alpha);
		if(!rgb_image)
		{
			throw std::runtime_error("Unable to load image");
		}

		auto _ = gsl::finally([rgb_image]()
		{
			stbi_image_free(rgb_image);
		});

		const auto size = this->width * this->height * 4;
		this->data.resize(size);
		
		std::memmove(this->data.data(), rgb_image, size);
	}

	int image::get_width() const
	{
		return this->width;
	}

	int image::get_height() const
	{
		return this->height;
	}

	const void* image::get_buffer() const
	{
		return this->data.data();
	}

	size_t image::get_size() const
	{
		return this->data.size();
	}

	const std::string& image::get_data() const
	{
		return this->data;
	}

	gif::gif(const std::string& gif_data)
	{
		int channels{};
		auto* rgb_image = stbi_load_gif_from_memory(reinterpret_cast<const uint8_t*>(gif_data.data()), 
			static_cast<int>(gif_data.size()), 
			&this->frame_delays, 
			&this->width, 
			&this->height,
			&this->frame_count,
			&channels, 
			STBI_rgb_alpha);
		if(!rgb_image)
		{
			throw std::runtime_error("Unable to load image");
		}

		auto _ = gsl::finally([rgb_image]()
		{
			stbi_image_free(rgb_image);
		});

		const auto size = this->width * this->height * 4;
		this->data.resize(size);
		
		std::memmove(this->data.data(), rgb_image, size);

	}
	int gif::get_width() const
	{
		return this->width;
	}

	int gif::get_height() const
	{
		return this->height;
	}

	const void* gif::get_buffer() const
	{
		return this->data.data();
	}

	size_t gif::get_size() const
	{
		return this->data.size();
	}

	const std::string& gif::get_data() const
	{
		return this->data;
	}

	int gif::get_frame_count() const
	{
		return this->frame_count;
	}

	int* gif::get_frame_delays() const
	{
		return this->frame_delays;
	}
}
