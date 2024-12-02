plugins {
    id("java")
    id("com.gradleup.shadow") version "9.0.0-beta2"
}

group = "org.operator"
version = "1.0-SNAPSHOT"

repositories {
    mavenCentral()
}

tasks.jar{
    manifest {
        attributes["Main-Class"] = "org.operator.Main"
    }
}

dependencies {
    // https://mvnrepository.com/artifact/com.fazecast/jSerialComm
    implementation("com.fazecast:jSerialComm:1.3.10")
}