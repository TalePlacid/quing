.pragma library

function saveSnapshot(item, filePath, onSaved) {
    var result = item.grabToImage(function(grabResult) {
        grabResult.saveToFile(filePath)

        if (onSaved !== undefined && onSaved !== null) {
            onSaved()
        }
    })

    return result
}
