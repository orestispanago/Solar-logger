CREATE TABLE `collector`.`measurements_test` (
    `id` INT NOT NULL AUTO_INCREMENT,
    `time` DATETIME NULL DEFAULT CURRENT_TIMESTAMP,
    `count` INT NULL,
    `Tabd` FLOAT NULL,
    `TabdS` FLOAT NULL,
    `Tabu` FLOAT NULL,
    `TabuS` FLOAT NULL,
    `Tafd` FLOAT NULL,
    `TafdS` FLOAT NULL,
    `Tafmd` FLOAT NULL,
    `TafmdS` FLOAT NULL,
    `Tafmu` FLOAT NULL,
    `TafmuS` FLOAT NULL,
    `Tafu` FLOAT NULL,
    `TafuS` FLOAT NULL,
    `Tim` FLOAT NULL,
    `TimS` FLOAT NULL,
    `Tenv` FLOAT NULL,
    `TenvS` FLOAT NULL,
    `Tout` FLOAT NULL,
    `ToutS` FLOAT NULL,
    `Tin` FLOAT NULL,
    `TinS` FLOAT NULL,
    `Tenv2` FLOAT NULL,
    `Tenv2S` FLOAT NULL,
    `RH` FLOAT NULL,
    `RHS` FLOAT NULL,
    `Irr` FLOAT NULL,
    `IrrS` FLOAT NULL,
    `Wind` FLOAT NULL,
    `WindS` FLOAT NULL,
    `Flow` FLOAT NULL,
    `FlowS` FLOAT NULL,
    PRIMARY KEY (`id`)
);