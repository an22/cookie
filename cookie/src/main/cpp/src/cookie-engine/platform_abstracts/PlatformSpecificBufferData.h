//
// Created by Antiufieiev Michael on 08.08.2021.
//

#ifndef COOKIE_ENGINE_PLATFORMSPECIFICBUFFERDATA_H
#define COOKIE_ENGINE_PLATFORMSPECIFICBUFFERDATA_H
namespace cookie {

	enum class BufferType {
		VERTEX_BUFFER
	};

	struct PlatformSpecificBufferData {
		virtual ~PlatformSpecificBufferData() = default;
	};
}
#endif //COOKIE_ENGINE_PLATFORMSPECIFICBUFFERDATA_H
