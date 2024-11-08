#pragma once

#include <SFML/Graphics.hpp>
#include <cmath>
#include <optional>
#include <random>

namespace vm {
	const float PI = 3.14159265f;

	inline float magnitude(const sf::Vector2f& v) noexcept {
		return std::sqrt(v.x * v.x + v.y * v.y);
	}

	inline float vectorToAngleDegrees(const sf::Vector2f& v) noexcept {
		return std::atan2(v.y, v.x) * 180.f / PI;
	}

	inline float vectorToAngleRadians(const sf::Vector2f& v) noexcept {
		return std::atan2(v.y, v.x);
	}

	inline sf::Vector2f angleDegreesToVector(float angle) noexcept {
		return sf::Vector2f(std::cos(angle * PI / 180.f), std::sin(angle * PI / 180.f));
	}

	inline sf::Vector2f angleRadiansToVector(float angle) noexcept {
		return sf::Vector2f(std::cos(angle), std::sin(angle));
	}

	inline float degreesToRadians(float degrees) noexcept {
		return degrees * PI / 180.f;
	}

	inline float radiansToDegrees(float radians) noexcept {
		return radians * 180.f / PI;
	}

	inline sf::Vector2f normalize(const sf::Vector2f& v) noexcept {
		float len = magnitude(v);
		if (len != 0) {
			return sf::Vector2f(v.x / len, v.y / len);
		}
		return v;
	}

	inline float distance(const sf::Vector2f& v1, const sf::Vector2f& v2) noexcept {
		return magnitude(v1 - v2);
	}

	inline float dot(const sf::Vector2f& v1, const sf::Vector2f& v2) noexcept {
		return v1.x * v2.x + v1.y * v2.y;
	}

	inline float angleBetweenVectorsDegrees(const sf::Vector2f& v1, const sf::Vector2f& v2) noexcept {
		return std::acos(dot(v1, v2) / (magnitude(v1) * magnitude(v2)));
	}

	inline sf::Vector2f limit(const sf::Vector2f& v, float max) noexcept {
		if (magnitude(v) > max) {
			return normalize(v) * max;
		}
		return v;
	}

	inline sf::VertexArray createVectorLine(const sf::Vector2f& position, const sf::Vector2f& direction, const sf::Color& color) noexcept {
		sf::VertexArray vector(sf::Lines, 2);
		vector[0].position = position;
		vector[0].color = color;
		vector[1].position = position + direction;
		vector[1].color = color;
		return vector;
	}

	inline float normalizeAngle(float angle, float min = 0.f, float max = 360.f) noexcept {
		while (angle < min) angle += 360;
		while (angle >= max) angle -= 360;
		return angle;
	}

	inline float clampAngleInDegrees(float angle, float refAngle, float maxOffset) noexcept {
		float diff = angle - refAngle;
		if (diff > maxOffset) return refAngle + maxOffset;
		if (diff < -maxOffset) return refAngle - maxOffset;
		return angle;
	}

	inline sf::Vector2f rotateAngleInDegrees(const sf::Vector2f& vector, float angleInDeg) noexcept {
		float rad = angleInDeg * PI / 180.0f;
		return sf::Vector2f(
			vector.x * std::cos(rad) - vector.y * std::sin(rad),
			vector.x * std::sin(rad) + vector.y * std::cos(rad)
		);
	}

	inline float angleBetweenVectorsRadians(const sf::Vector2f& v1, const sf::Vector2f& v2) noexcept {
		return angleBetweenVectorsDegrees(v1, v2) * PI / 180.f;
	}

	inline std::optional<sf::Vector2f> getIntersection(
		const sf::Vector2f& p1, const sf::Vector2f& p2,
		const sf::Vector2f& p3, const sf::Vector2f& p4) {

		float denominator = (p1.x - p2.x) * (p3.y - p4.y) - (p1.y - p2.y) * (p3.x - p4.x);

		if (denominator == 0) {
			// Lines are parallel or coincident
			return std::nullopt;
		}

		float x = ((p1.x * p2.y - p1.y * p2.x) * (p3.x - p4.x) - (p1.x - p2.x) * (p3.x * p4.y - p3.y * p4.x)) / denominator;
		float y = ((p1.x * p2.y - p1.y * p2.x) * (p3.y - p4.y) - (p1.y - p2.y) * (p3.x * p4.y - p3.y * p4.x)) / denominator;

		return sf::Vector2f(x, y);
	}

	inline bool isInFront(const sf::Vector2f& movingPos, const sf::Vector2f& stationaryPos, const sf::Vector2f& travelDirection) noexcept {
		sf::Vector2f vectorToObject = stationaryPos - movingPos;
		float angleToObject = atan2(vectorToObject.y, vectorToObject.x);
		float travelAngle = atan2(travelDirection.y, travelDirection.x);
		float angleDifference = atan2(sin(travelAngle - angleToObject), cos(travelAngle - angleToObject));
		return fabs(angleDifference) > PI / 2;
	}

	inline float distanceToLine(const sf::Vector2f& lineStart, const sf::Vector2f& lineEnd, const sf::Vector2f& point) noexcept {
		sf::Vector2f line = lineEnd - lineStart;
		sf::Vector2f pointToLineStart = point - lineStart;
		float projection = dot(pointToLineStart, normalize(line));
		sf::Vector2f closestPoint = lineStart + normalize(line) * projection;
		return distance(point, closestPoint);
	}

	inline sf::Vector2f closestPointOnLine(const sf::Vector2f& lineStart, const sf::Vector2f& lineEnd, const sf::Vector2f& point) noexcept {
		sf::Vector2f line = lineEnd - lineStart;
		sf::Vector2f pointToLineStart = point - lineStart;
		float projection = dot(pointToLineStart, normalize(line));
		return lineStart + normalize(line) * projection;
	}

	template <typename T>
	inline T randomValue(const T& min, const T& max) {
		std::random_device rd;
		std::mt19937 gen(rd());

		if constexpr (std::is_integral_v<T>) {
			std::uniform_int_distribution<T> dis(min, max);
			return dis(gen);
		}
		else if constexpr (std::is_floating_point_v<T>) {
			std::uniform_real_distribution<T> dis(min, max);
			return dis(gen);
		}
		else {
			static_assert(std::is_arithmetic_v<T>, "Type must be integral or floating-point/doubles.");
		}
	}

	template <typename T>
	inline T setSignificantFigures(const T& value, int numFigures) {
		T factor = std::pow(10, numFigures);
		return std::round(value * factor) / factor;
	}

	inline sf::Vector2f relativeRotationTransformedPosition(const sf::Vector2f& obj1Position, const sf::Vector2f& obj2Offset, float rotationInDegrees) noexcept {
		sf::Transform transform;
		transform.rotate(rotationInDegrees, obj1Position);
		return transform.transformPoint(obj1Position + obj2Offset);
	}
}
