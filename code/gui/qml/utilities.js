.pragma library

function getEvalItemColor(level) {
    switch(level)
    {
        case 0:
            return "green"
        case 1:
            return "lightgreen"
        case 2:
            return "yellow"
        case 3:
            return "#ff6666"
        case 4:
            return "red"
        default:
            return "transparent"
    }
}
